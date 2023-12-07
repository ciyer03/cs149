/**
 * Description: This program multiplies the supplied A matrices, and each W matrix.
 * The program then accepts from stdin. It uses multiple child processes to achieve
 * this a faster way.
 *
 * Author names: Chandramouli Iyer
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: December 6th
 * Creation date: December 6th
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_ROWS 8
#define MAX_COLUMNS 8
#define PRODUCT (MAX_ROWS * MAX_COLUMNS)
#define FN_SIZE 15 // Assuming filenames (PID.out and PID.err) won't each exceed 15 characters.

int fd[MAX_COLUMNS][2];
int realSTDOUT;
clock_t start, end, input_start, input_end;
double cpu_time_used, input_time;

int calcResult(char *inputMatrix, char **wMatrices, const int wMatricesNum);
int gatherAMatrix(const int numWMatrices);
void freeMem(char **dynMatrix, const int items);

int main(int argc, char *argv[]) {
	start = clock();
	if (argc < 3) {
		fprintf(stderr, "You must pass in at least 2 matrices as input.\n");
		return 1;
	}

	realSTDOUT = dup(STDOUT_FILENO);

	int numWMatrices = argc - 2;
	// Create pipes for IPC.
	for (int i = 0; i < numWMatrices; ++i) {
		if (pipe(fd[i]) == -1) {
			fprintf(stderr, "Pipe creation failed.\n");
			return 1;
		}
	}

	char **wMatrices = (char **)malloc(sizeof(char *) * numWMatrices);
	if (wMatrices == NULL) {
		fprintf(stderr, "Memory allocation failed for wMatrices.\n");
		return 1;
	}

	// Store the names into wMatrices.
	for (int i = 0; i < numWMatrices; ++i) {
		wMatrices[i] = strdup(argv[i + 2]);
	}

	if (calcResult(argv[1], wMatrices, numWMatrices) == 1) {
		fprintf(stderr, "Calculating result failed. Refer to prior messages for cause.\n");
		freeMem(wMatrices, numWMatrices);
		return 1;
	}

	freeMem(wMatrices, numWMatrices);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	cpu_time_used -= input_time;

	printf("\nRun time: %f secs\n", cpu_time_used);

	return 0;
}

/**
 * Does matrix multiplication with the passed in inputMatrix. Passes the
 * inputMatrix and one wMatrix to a child process.
 *
 * @param inputMatrix The A matrix.
 * @param wMatrices The array containing all passed in W matrices.
 * @param wMatricesNum The number of W matrices passed in.
 *
 * @return 1 on failure, 0 on success. On failure, check stderr and/or PID.err
 * files for the reason.
 *
 **/
int calcResult(char *inputMatrix, char **wMatrices, const int numWMatrices) {
	char outFile[FN_SIZE];
	char errFile[FN_SIZE];
	int outFD = -1;
	int errFD = -1;

	for (int i = 0; i < numWMatrices; ++i) {
		pid_t pid = fork();
		if (pid < 0) {
			fprintf(stderr, "fork() failed.\n");
			return 1;
		} else if (pid == 0) {
			// Close all unnecessary read and write ends of the pipe.
			for (int j = 0; j < MAX_COLUMNS; ++j) {
				if (j != i) {
					close(fd[j][0]);
					close(fd[j][1]);
				}
			}

			pid_t childPID = getpid();

			snprintf(outFile, FN_SIZE, "%d.out", childPID);
			snprintf(errFile, FN_SIZE, "%d.err", childPID);

			// Create the actual files on disk, open in write only and append mode,
			// and ensure data integrity.
			outFD = open(outFile, O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0644);
			errFD = open(errFile, O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0644);

			// Redirect stderr and stdout to errFile and outFile respectively.
			if ((dup2(errFD, STDERR_FILENO) == -1) || (dup2(outFD, STDOUT_FILENO) == -1)) {
				fprintf(stderr, "Redirecting stderr and stdout failed.\n");
				return 1;
			}

			fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", i + 1, childPID, getppid());
			fflush(stdout); // Ensure that any pending writes have been written.

			// Redirect all stdin to the read end of the pipe.
			if (dup2(fd[i][0], STDIN_FILENO) == -1) {
				fprintf(stderr, "Redirecting stdin and stdout to pipe read and write ends failed.\n");
				return 1;
			}

			char realSOUT[12];
			snprintf(realSOUT, sizeof(realSOUT), "%d", realSTDOUT);

			char *args[] = {"matrixmult_parallel", inputMatrix, wMatrices[i], realSOUT, NULL};
			if (execv("./matrixmult_parallel.o", args) == -1) {
				// Error handling.
				fprintf(stderr, "execv() failed. Command tried to execute: %s %s %s %s\n", "./matrixmult_parallel.o", args[1], args[2], args[3]);
				close(outFD);
				close(errFD);
				close(fd[i][0]);
				close(fd[i][1]);
				return 1;
			}
		}
	}

	if (dup2(realSTDOUT, STDOUT_FILENO) == -1) {
		fprintf(stderr, "Redirecting stdout to terminal failed.\n");
		return 1;
	}

	if (gatherAMatrix(numWMatrices) == 1) {
		fprintf(stdout, "Sending matrices from stdin failed. Refer to prior messages for cause.\n");
		return 1;
	}

	// Parent process
	for (int i = 0; i < numWMatrices; ++i) {
		int wstatus;
		int childPID = wait(&wstatus); // Wait for each child process to end.

		// Create a string that results in PID.out and PID.err, where PID is the PID
		// of the process, and store that in the char array out_file and err_file
		// respectively.
		snprintf(outFile, FN_SIZE, "%d.out", childPID);
		snprintf(errFile, FN_SIZE, "%d.err", childPID);

		// Open the specific child's stdout and stderr files in write only and
		// append mode.
		outFD = open(outFile, O_WRONLY | O_APPEND | O_DSYNC, 0644);
		errFD = open(errFile, O_WRONLY | O_APPEND | O_DSYNC, 0644);

		// Redirect stdout and stderr to out_file and err_file respectively.
		dup2(outFD, STDOUT_FILENO);
		dup2(errFD, STDERR_FILENO);

		fprintf(stdout, "Finished child %d pid of parent %d\n", childPID, getpid());
		fflush(stdout);

		if (WIFEXITED(wstatus)) {
			// Check if the child process exited normally.
			int exitStatus = WEXITSTATUS(wstatus); // Store exit code of child process.

			if (exitStatus == 0) {
				// If the child process exited with code 0 (success)
				fprintf(stdout, "Exited with exitcode = %d\n", exitStatus);
				fflush(stdout);
			} else {
				fprintf(stderr, "Exited with exitcode = %d\n", exitStatus);
			}
		} else if (WIFSIGNALED(wstatus)) {
			// Handle signals.
			fprintf(stderr, "Killed with signal %d\n", WTERMSIG(wstatus));
		}

		fflush(stdout);
		fflush(stderr);

		// Close read end of pipe.
		close(fd[i][0]);
	}

	if (dup2(realSTDOUT, STDOUT_FILENO) == -1) {
		fprintf(stderr, "Redirecting stdout to terminal failed.\n");
		return 1;
	}

	// Close all fds
	close(outFD);
	close(errFD);

	return 0;
}

/**
 * Gathers A matrices sequentially from stdin and then passes them off to the
 * child processes.
 *
 * @param numWMatrices The number of W matrices. Directly corresponds to the
 * number of child processes.
 *
 * @return 1 on error, 0 on success. On failure, check stderr and/or PID.err
 * files for the reason.
 *
 **/
int gatherAMatrix(const int numWMatrices) {
	char *aMatrix = NULL;
	size_t bufferLen = 0;

	fprintf(stdout, "Enter file path of an A Matrix: \n");
	fflush(stdout);

	input_start = clock();

	while (getline(&aMatrix, &bufferLen, stdin) != -1) {
		input_end = clock();
		input_time += ((double)(input_end - input_start)) / CLOCKS_PER_SEC;
		size_t len = strlen(aMatrix);

		// Remove the trailing newline character.
		if (len > 0 && aMatrix[len - 1] == '\n') {
			aMatrix[len - 1] = '\0';
			len--;
		}

		if (len > 0) {
			for (int i = 0; i < numWMatrices; ++i) {
				// Pass the length of the file passed to each child process.
				if (write(fd[i][1], &len, sizeof(size_t)) == -1) {
					fprintf(stderr,
					        "Sending length of A matrix %s text to child %d failed.\n", aMatrix, i);
					return 1;
				}

				// Pass the filename to each child process.
				if (write(fd[i][1], aMatrix, len) == -1) {
					fprintf(stderr, "Sending A matrix %s to child %d failed.\n", aMatrix, i);
					return 1;
				}
			}
		}

		// Free the space allocated for the filename and reset.
		free(aMatrix);
		aMatrix = NULL;
		bufferLen = 0;
		fprintf(stdout, "Enter file path of an A Matrix (Ctrl+D to exit): \n");
		input_start = clock();
	}

	input_end = clock();
	input_time += ((double)(input_end - input_start)) / CLOCKS_PER_SEC;

	// Indicate EOF to each child process and close all the pipes.
	for (int i = 0; i < numWMatrices; ++i) {
		bufferLen = 0;
		if (write(fd[i][1], &bufferLen, sizeof(size_t)) == -1) {
			fprintf(stderr, "Sending EOF to child %d failed.\n", i);
			return 1;
		}

		close(fd[i][1]);
	}

	if (aMatrix != NULL) {
		free(aMatrix);
		aMatrix = NULL;
	}

	return 0;
}

/**
 * Frees the memory allocated for the given matrix.
 *
 * @attention The provided matrix must be dynamically allocated, and have EXACTLY
 *"items" number of items stored in this array. This function only frees "items"
 * number of memory from the matrix.
 *
 * @param matrix The dynamically allocated array whose memory needs to be freed.
 * @param items The number of items that have been stored in this array.
 *
 **/
void freeMem(char **dynMatrix, const int items) {
	for (int i = 0; i < items; ++i) {
		free(dynMatrix[i]);
	}
	free(dynMatrix);
	dynMatrix = NULL;
}
