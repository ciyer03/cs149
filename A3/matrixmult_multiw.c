/**
 * Description: This program multiplies two 8x8 matrices, and prints out the matrix to 
 * stdout. It uses multiple child processes to achieve this a faster way.
 * Author names: Chandramouli Iyer, Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu, safiullah.saif@sjsu.edu
 * Last modified date: October 11th
 * Creation date: October 4th
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
 
#define MAX_COLUMNS 8
#define MAX_ROWS 8
#define FN_SIZE 15 // File name size

/**
 * Executes the program. Accepts command line parameters.
 *
 * Input parameters: argc: The number of arguments that have been passed to the program.
 *                   Is at least always one, and increases as more parameters get passed.
 *                   argv[]: Contains the passed in arguments themselves in an array. 
 *                   Is at least always one (the program itself), and increases as more 
 *                   parameters get passed.
 * 
 * Returns: An integer which indicates if the program exited successfully or not. 
 * Anything apart from 0 indicates failure.
 **/
int main(int argc, char *argv[]) {
    // Checks if there are at least 3 arguments (2 files, and 1 default).
    if (argc < 3) {
        printf("error: expecting at least 2 files as input\n");
        printf("Terminating, exit code 1.\n");
        return 1;
    }

    char out_file[FN_SIZE];
    char err_file[FN_SIZE];
    int out_fd;
    int err_fd;

    int numWMatrices = argc - 2; // Gets the number of W matrces passed on the command line.
    for (int i = 0; i < numWMatrices; ++i) {
        int preChild[2];
        if (pipe(preChild) == -1) {
            printf("Pipe creation failure.\n");
            return 1; 
        }

        pid_t pid = fork();
        if (pid < 0) {
            printf("fork() error.");
            return 1;
        } else if (pid == 0) {
            close(preChild[1]);

            int childPID = getpid();
            int out_size;
            int err_size;

            // Reads in the filename sizes for both files.
            if (read(preChild[0], &out_size, sizeof(int)) == -1) {
                printf("Read error in child pid %d, for reading out_file size.\n", childPID);
                close(preChild[0]);
                return 1;
            }

            if (read(preChild[0], &err_size, sizeof(int)) == 1) {
                printf("Read error in child pid %d, for reading err_file size.\n", childPID);
                close(preChild[0]);
                return 1;
            }

            // Reads in the filename created by the parent process. Mainly to ensure that the files for the 
            // child process have been created.
            if (read(preChild[0], out_file, out_size) == -1) {
                printf("Read error in child pid %d, for reading stdout filename.\n", childPID);
                close(preChild[0]);
                return 1;
            }

            if (read(preChild[0], err_file, err_size) == -1) {
                printf("Read error in child pid %d, for reading stderr filename.\n", childPID);
                close(preChild[0]);
                return 1;
            }
            close(preChild[0]);

            // Create the actual files on disk, open in write only and append mode, and ensure data integrity.
            out_fd = open(out_file, O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0777);
            err_fd = open(err_file, O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0777);

            // Redirect stdout and stderr to out_file and err_file respectively.
            dup2(out_fd, STDOUT_FILENO);
            dup2(err_fd, STDERR_FILENO);

            int matrixNum = argc - (numWMatrices - i); // Gets the index of the W matrix to pass.
            fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", i + 1, childPID, getppid());
            fflush(stdout); // Ensure that any pending writes have been written.

            // Call matrixmult with the A matrix and a W matrix specified by the index.
            if (execl("./matrixmult", "matrixmult", argv[1], argv[matrixNum], out_file, err_file, NULL) == -1) {
                fprintf(stderr, "execl() failed. Command tried to execute: %s %s %s %s %s", "./matrixmult", 
                        argv[1], argv[2], out_file, err_file);
                close(out_fd);
                close(err_fd);
                return 1;
            }
        } else {
            close(preChild[0]);

            // Create a string that results in PID.out and PID.err, where PID is the PID of the 
            // process, and store that in the char array out_file and err_file respectively.
            snprintf(out_file, sizeof(out_file), "%d.out", pid);
            snprintf(err_file, sizeof(err_file), "%d.err", pid);

            int out_size = strlen(out_file);
            int err_size = strlen(err_file);

            // Give the size of out_file to the child process.
            if (write(preChild[1], &out_size, sizeof(int)) == -1) {
                printf("Write error while writing the size of out_file, %d, to child pid %d.\n", out_size, pid);
                close(preChild[1]);
                return 1;
            }

            // Give the size of err_file to the child process.
            if (write(preChild[1], &err_size, sizeof(int)) == -1) {
                printf("Write error while sending the size of err_file, %d, to child pid %d.\n", err_size, pid);
                close(preChild[1]);
                return 1;
            }

            // Give the name of the out_file to the child process.
            if (write(preChild[1], out_file, out_size) == -1) {
                printf("Write error for sending filename %s to child pid %d.\n", out_file, pid);
                close(preChild[1]);
                return 1;
            }

            // Give the name of the err_file to the child process.
            if (write(preChild[1], err_file, err_size) == -1) {
                printf("Write error for sending filename %s to child pid %d.\n", err_file, pid);
                close(preChild[1]);
                return 1;
            }
            close(preChild[1]);
        }
    }

    // Parent process. Wait for child processes to exit.
    for (int i = 0; i < numWMatrices; ++i) {
        int wstatus;
        int childPID = wait(&wstatus); // Wait for each child process to end.

        // Open the specific child's stdout and stderr files in write only and append mode.
        out_fd = open(out_file, O_WRONLY | O_APPEND | O_DSYNC, 0777);
        err_fd = open(err_file, O_WRONLY | O_APPEND | O_DSYNC, 0777);

        // Redirect stdout and stderr to out_file and err_file respectively.
        dup2(out_fd, STDOUT_FILENO);
        dup2(err_fd, STDERR_FILENO);

        fprintf(stdout, "Finished child %d pid of parent %d\n", childPID, getpid());

        if (WIFEXITED(wstatus)) { // Check if the child process exited normally.
            int exitStatus = WEXITSTATUS(wstatus); // Store exit code of child process.

            if (exitStatus == 0) { // If the child process exited with code 0 (success)
                fprintf(stdout, "Exited with exitcode = %d\n", exitStatus);
            } else {
                fprintf(stderr, "Exited with exitcode = %d\n", exitStatus);
                return 1;
            }
        } else if (WIFSIGNALED(wstatus)) {
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(wstatus));
            return 1;
        }

        close(out_fd);
        close(err_fd);

        return 0;
    }
}
