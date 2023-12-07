/**
 * Description: This program multiplies the supplied W matrices, and A matrix. From that, it creates a RSum 
 * matrix. The program then accepts from stdin. It then multiplies each supplied matrix with the previously 
 * created RSum matrix, 
 * stdout. It uses multiple child processes to achieve this a faster way.
 * Author names: Chandramouli Iyer
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: December 6th
 * Creation date: December 6th
 **/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define MAX_ROWS 8
#define MAX_COLUMNS 8
#define PRODUCT (MAX_ROWS * MAX_COLUMNS)
#define FN_SIZE 15 // Assuming filenames (PID.out and PID.err) won't each exceed 15 characters.

double rSumMatrix[MAX_ROWS][MAX_COLUMNS];
char *rMatrixFilename = "R1.txt";
int numMatricesCalculated;
double childResult[MAX_ROWS][MAX_COLUMNS];
int stdoutFD;
clock_t start, end, input_start, input_end;
double cpu_time_used, input_time;


int aggregateFiles();
int getRMatrix(char *input, char** matrices, const int numMatrices);
void sumRMatrix();
void writeRMatrix();
void zeroOut(double *matrix);
void printRMatrix();
void freeMem(char **matrix, int items);

int main(int argc, char *argv[]) {
    start = clock();
    int exitStatus = 0;
    if (argc < 3) {
        printf("error: expecting at least 2 files as input.\n");
        printf("Terminating, exit code 1.\n");
        return 1;
    }

    // Env variable to track if provided matrix is the RSumMatrix or not. "1" indicates RSumMatrix.
    if (setenv("IS_R_MATRIX", "0", 1) == -1) {
        printf("Failed to set env variable.\n");;
        return 1;
    }

    // Store original STDOUT_FILENO for later reset.
    stdoutFD = dup(STDOUT_FILENO);

    // Dynamically allocate memory for all the provided matrices.
    int numWMatrices = argc - 2;
    char **wMatrices = (char**) malloc(numWMatrices * sizeof(char *));
    if (wMatrices == NULL) {
        printf("Memory allocation failed for wMatrices.\n");
        return 1;
    }

    // Store the names into wMatrices.
    for (int i = 0; i < numWMatrices; ++i) {
        wMatrices[i] = strdup(argv[i + 2]);
    }

    // Calculate the initial R matrix.
    if ((exitStatus = getRMatrix(argv[1], wMatrices, (argc - 2))) == 1) {
        printf("Calculating RSumMatrix failed. Refer to prior messages for the reason.\n");
        freeMem(wMatrices, numWMatrices);
        return exitStatus;
    }

    // Free the memory allocated for the wMatrices array.
    freeMem(wMatrices, numWMatrices);

    // Gather files from stdin and calculate R matrix accordingly. exitStatus of one indicates an error.
    if ((exitStatus = aggregateFiles()) == 1) {
        printf("Calculating RSumMatrix failed. Refer to prior messages, either on the terminal in the PID.err for the reason.\n");
        return exitStatus;
    }

    printRMatrix();
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cpu_time_used -= input_time;

    printf("\nRun time: %f secs\n", cpu_time_used);
    return exitStatus;
}

/**
 * Takes files from the user, allocates the required amount of memory, and passes it over to getRMatrix().
 * 
 * Assumption: Files passed in are valid files, contain only integers, the files actually exist, files are 
 * separated by spaces, and there are no spaces in file names.
 **/
int aggregateFiles() {
    char *userLineBuffer = NULL;
    size_t userBufferLen = 0;
    char *userBufferDup = NULL;

    // Set env variable to 1 since we will be passing the R matrix from now on.
    if (setenv("IS_R_MATRIX", "1", 1) == -1) {
        printf("Failed to set env variable.\n");
        return 1;
    }

    fprintf(stdout, "Enter file paths: \n");
    fflush(stdout);

    input_start = clock();
    // Gathers files as user inputs. getline() automatically allocates required memory. Continues until user 
    // presses Ctrl+D.
    while (getline(&userLineBuffer, &userBufferLen, stdin) != -1) {
        input_end = clock();
        input_time += ((double) (input_end - input_start)) / CLOCKS_PER_SEC;
        size_t len = strlen(userLineBuffer);

        // Remove the trailing newline character.
        if (len > 0 && userLineBuffer[len - 1] == '\n') {
            userLineBuffer[len - 1] = '\0';
        }

        // Duplicate the user string so it can be used later.
        userBufferDup = strdup(userLineBuffer);

        // Calculate how many files were passed in. Tokenize by spaces.
        char *wMatrix = strtok(userLineBuffer, " ");
        int numFiles = 0;
        while (wMatrix != NULL) {
            numFiles++;
            wMatrix = strtok(NULL, " ");
        }

        // Only need to pass files if there's at least one.
        if (numFiles > 0) {
            // Allocate required amount of memory for the files.
            char **wMatrices = malloc(numFiles * sizeof(char *));
            if (wMatrices == NULL) { // Error handling
                printf("Memory allocation failed.\n");
                if (userLineBuffer != NULL) { 
                    free(userLineBuffer);
                    userLineBuffer = NULL;
                }

                if (userBufferDup != NULL) {
                    free(userBufferDup);
                    userBufferDup = NULL;
                }
                return 1;
            }

            // Use the duplicated string to gather file names. Store them in the allocated array.
            wMatrix = strtok(userBufferDup, " ");
            int i = 0;
            while (wMatrix != NULL) {
                wMatrices[i] = strdup(wMatrix);
                ++i;
                wMatrix = strtok(NULL, " ");
            }

            // No need for the duplicated string anymore. Free the space.
            if (userBufferDup != NULL) {
                free(userBufferDup);
                userBufferDup = NULL;
            }

            // Pass over the files to getRMatrix().
            if (getRMatrix(rMatrixFilename, wMatrices, numFiles) == 1) { // Error handling.
                printf("Calculating RSumMatrix failed for stdout files.\n");
                freeMem(wMatrices, numFiles);

                if (userLineBuffer != NULL) { 
                    free(userLineBuffer);
                    userLineBuffer = NULL;
                }

                return 1;
            }

            // Free the allocated memory.
            freeMem(wMatrices, numFiles);
            if (userLineBuffer != NULL) { 
                free(userLineBuffer);
                userLineBuffer = NULL;
            }

            fprintf(stdout, "Enter file paths (Ctrl+D to exit): \n");
            fflush(stdout);
            input_start = clock();
        }
    }
    input_end = clock();
    input_time += ((double) (input_end - input_start)) / CLOCKS_PER_SEC;
    

    // Catches some weird edge cases.
    if (userLineBuffer != NULL) { 
        free(userLineBuffer);
        userLineBuffer = NULL;
    }

    if (userBufferDup != NULL) {
        free(userBufferDup);
        userBufferDup = NULL;
    }

    return 0;
}

/**
 * Calculates the RSumMatrix. Sends the inputMatrix along wih passed in matrices to be multiplied. Sums up the 
 * result of each inputMatrix * Wi.txt where i is the i'th file that's passed. Stores the sum in rSumMatrix. 
 * Resets the rSumMatrix for each call.
 * 
 * Assumption: Files passed in are valid files, contain only integers, the files actually exist, files are 
 * separated by spaces, and there are no spaces in file names.
 *
 * Input: char *inputMatrix -> The matrix with which all W matrices will be multiplied with.
 *        char **wMatrices -> The dynamically allocated array that contains the filepath of all W matrices.
 *        const int numMatrices -> The number of W matrices.
 **/
int getRMatrix(char *inputMatrix, char **wMatrices, const int numMatrices) {
    char outFile[FN_SIZE];
    char errFile[FN_SIZE];
    int outFD = -1;
    int errFD = -1;
    int pipes[numMatrices][2];

    // Reset the rSumMatrix so that the results are for the currently passed in matrices.
    zeroOut(&rSumMatrix[0][0]);

    // Set up pipes for communication.
    for (int i = 0; i < numMatrices; ++i) {
        if (pipe(pipes[i]) == -1) {
            printf("Error while creating pipes.\n");
            return 1;
        }
    }

    // Sends in the inputMatrix and each of the the W matrices one by one to matrixmult_parallel which 
    // calculates the product of the inputMatrix and the Wi'th matrix.
    for (int i = 0; i < numMatrices; ++i) {
        pid_t pid = fork();

        // Keep track of how many matrices we have calculated.
        numMatricesCalculated++;
        if (pid < 0) {
            printf("fork() failed for process number %d.\n", i);
            return 1;
        } else if (pid == 0) { // Child process.
            pid_t pid = getpid();
            // Close unneeded read and write ends.
            for (int j = 0; j < numMatrices; ++j) {
                close(pipes[j][0]);
                if (j != i) { // Only need to write to this child process' specific write end.
                    close(pipes[j][1]);
                }
            }

            snprintf(outFile, FN_SIZE, "%d.out", pid);
            snprintf(errFile, FN_SIZE, "%d.err", pid);

            // Create the actual files on disk, open in write only and append mode, and ensure data integrity.
            outFD = open(outFile, O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0644);
            errFD = open(errFile, O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0644);

            // Redirect stderr and stdout to errFile and outFile respectively.
            if ((dup2(errFD, STDERR_FILENO) == -1) || (dup2(outFD, STDOUT_FILENO) == -1)) {
                printf("Redirecting stderr and stdout failed.\n");
                return 1;
            }

            fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", 
                    numMatricesCalculated, pid, getppid());
            fflush(stdout); // Ensure that any pending writes have been written.

            // Only needed to route that for the above message.
            close(outFD);

            // Reset stdout to the terminal first.
            dup2(stdoutFD, STDOUT_FILENO);

            // Redirect all stdout to the write end of the pipe.
            if (dup2(pipes[i][1], STDOUT_FILENO) == -1) {
                printf("Redirecting stdout to pipe read end failed.");
                return 1;
            }

            // After duplication, it's no longer needed.
            close(pipes[i][1]);

            // Pass in the original stdout file descriptor.
            char soutFDptr[12];
            snprintf(soutFDptr, sizeof(soutFDptr), "%d", stdoutFD);

            // Prepare the arguments for matrixmult_parallel.
            char *args[] = {"matrixmult_parallel",
                inputMatrix, wMatrices[i], outFile, errFile, soutFDptr, NULL};

            // Call matrixmult_parallel.
            if (execv("./matrixmult_parallel.o", args) == -1) { // Error handling.
                fprintf(stderr, "execv() failed. Command tried to execute: %s %s %s %s %s %s\n", 
                        "./matrixmult_parallel.o", args[1], args[2], args[3], args[4], args[5]);
                close(outFD);
                close(errFD);
                return 1;
            }
        }
    }

    int exitStatus = -1;

    // Parent process.
    for (int i = 0; i < numMatrices; ++i) {
        int wstatus;
        int childPID = wait(&wstatus); // Wait for each child process to end.

        // We are not going to write anything to the pipes.
        for (int j = 0; j < numMatrices; ++j) {
            close(pipes[j][1]);
        }

        // Create a string that results in PID.out and PID.err, where PID is the PID of the
        // process, and store that in the char array out_file and err_file respectively.
        snprintf(outFile, FN_SIZE, "%d.out", childPID);
        snprintf(errFile, FN_SIZE, "%d.err", childPID);

        // Open the specific child's stdout and stderr files in write only and append mode.
        outFD = open(outFile, O_WRONLY | O_APPEND | O_DSYNC, 0644);
        errFD = open(errFile, O_WRONLY | O_APPEND | O_DSYNC, 0644);

        // Reset stdout to the terminal.
        dup2(stdoutFD, STDOUT_FILENO);

        // Redirect stdout and stderr to out_file and err_file respectively.
        dup2(outFD, STDOUT_FILENO);
        dup2(errFD, STDERR_FILENO);

        fprintf(stdout, "Finished child %d pid of parent %d\n", childPID, getpid());
        fflush(stdout);

        if (WIFEXITED(wstatus)) { // Check if the child process exited normally.
            exitStatus = WEXITSTATUS(wstatus); // Store exit code of child process.

            if (exitStatus == 0) { // If the child process exited with code 0 (success)
                fprintf(stdout, "Exited with exitcode = %d\n", exitStatus);
                fflush(stdout);

                // On successful exit, read in the product matrix into childResult, sent by matrixmult_parallel.
                if (read(pipes[i][0], childResult, sizeof(double) * (MAX_ROWS * MAX_COLUMNS)) == -1) {
                    fprintf(stderr, "Reading R Matrix from child failed.\n");
                    return 1;
                }
                sumRMatrix(); // Sum up rSumMatrix and childResult matrices.

            } else {
                fprintf(stderr, "Exited with exitcode = %d\n", exitStatus);
            }
        } else if (WIFSIGNALED(wstatus)) { // Handle signals.
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(wstatus));
        }

        // Close read end of pipe.
        close(pipes[i][0]);
        fflush(stdout);
        fflush(stderr);
    }

    // Close all fds
    close(outFD);
    close(errFD);

    // Only write the rSumMatrix to disk if the child process was successful.
    if (exitStatus == 0) {
        writeRMatrix();
    }

    // Reset stdout to the terminal.
    dup2(stdoutFD, STDOUT_FILENO);
    return 0;
}

/**
 * Sums the given matrix and the rSumMatrix and stores the result in rSumMatrix.
 * 
 * Assumption: Both matrices are of size MAX_ROWS x MAX_COLUMNS
 *
 **/
void sumRMatrix() {
    double *rSum = &rSumMatrix[0][0];
    double *child = &childResult[0][0];

    for (int i = 0; i < PRODUCT; ++i) {
        *(rSum + i) += *(child + i);
    }
}

/**
 * Write the rSumMatrix to disk on a file named R1.txt.
 *
 * Assumption: rSumMatrix is of size MAX_ROWS * MAX_COLUMNS
 **/ 
void writeRMatrix() {
    double *matrix = &(rSumMatrix[0][0]);
    FILE *fd = fopen(rMatrixFilename, "w");

    for (int i = 0; i < PRODUCT; ++i) {
        if ((i % MAX_COLUMNS == 0) && i != 0) {
            fprintf(fd, "\n");
        }
        fprintf(fd, "%.2f ", *(matrix + i));
    }

    // Ensure that the contents have been written to disk, and close the file descriptor.
    fflush(fd);
    fclose(fd);
}

/**
 * Zeroes out the given matrix.
 *
 * Assumption: matrix is of size MAX_ROWS * MAX_COLUMNS
 *
 * Input: matrix -> The matrix to be zeroed out.
 **/
void zeroOut(double *matrix) {
    for (int i = 0; i < PRODUCT; ++i) {
        memset((matrix + i), 0, sizeof(double));
    }
}

/**
 * Frees the memory allocated for the given matrix.
 *
 * Input: char **matrix -> The dynamically allocated array whose memory needs to be freed.
 *        int items -> The number of items that have been stored in this array.
 *
 * Assumption: The provided matrix has been dynamically allocated, and EXACTLY "items" number of items stored
 * in this array.
 **/
void freeMem(char **matrix, int items) {
    for (int i = 0; i < items; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * Prints the rSumMatrix to stdout.
 * 
 * Assumption: The rSumMatrix is of size MAX_ROWS * MAX_COLUMNS
 **/
void printRMatrix() {
    double *matrix = &rSumMatrix[0][0];
    fprintf(stdout, "Rsum = [ ");
    for (int i = 0; i < PRODUCT; ++i) {
        if (i % MAX_COLUMNS == 0) {
            fprintf(stdout, "\n");
        }
        fprintf(stdout, "%.2f ", *(matrix + i));
    }
    fprintf(stdout, "\n]\n");
}
