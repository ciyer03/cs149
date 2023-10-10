/**
 * Description: This program multiplies two 8x8 matrices, and prints out the matrix to 
 * stdout. It uses multiple child processes to achieve this a faster way.
 * Author names: Chandramouli Iyer, Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu, safiullah.saif@sjsu.edu
 * Last modified date: October 4th
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
    // Checks if there are exactly four arguments (3 files, and 1 default).
    if (argc < 3) {
        printf("error: expecting at least 2 files as input\n");
        printf("Terminating, exit code 1.\n");
        return 1;
    }

    char out_file[15];
    char err_file[15];
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
        } else if (pid > 0) {
            close(preChild[0]);
            
            // Create a string that results in PID.out and PID.err, where PID is the PID of the 
            // process.
            snprintf(out_file, sizeof(out_file), "%d.out", pid);
            snprintf(err_file, sizeof(err_file), "%d.err", pid);

            // Create the actual files on disk, open in RW mode, and truncate them to length 0.
            out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            err_fd = open(err_file, O_RDWR | O_CREAT | O_APPEND, 0777);
            
            if (write(preChild[1], "Continue", 8) == -1) {
                printf("Write error.\n");
                return 1;
            }
        } else {
            close(preChild[1]);

            int matrixNum = argc - (numWMatrices - i); // Gets the index of the matrix to pass.
            // Call matrixmult with the A matrix and a W matrix specified by the index.
            if (execl("./matrixmult", "matrixmult", argv[1], argv[matrixNum], NULL) == -1) {
                printf("execv failed for matrix %d.\n", matrixNum);
                return 1;
            }
        }
    }

    // Parent process. Wait for child processes to exit.
    for (int i = 0; i < numWMatrices; ++i) {
        int wstatus;
        int childPID = wait(&wstatus); // Wait for each child process to end.

        if (WIFEXITED(wstatus)) { // Check if the child process exited normally.
            int exitStatus = WEXITSTATUS(wstatus); // Store exit code of child process.
            if (exitStatus == 0) { // If the child process exited with code 0 (success)
            } else {
                printf("Error with matrix %d. Child %d eited with code %d.\n", 
                       (argc - (numWMatrices - i)), childPID, exitStatus);
                return 1;
            }
        } else if (WIFSIGNALED(wstatus)) {
            // Implementation.
        }
    }
}
