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
#define FN_SIZE 15 // Assuming that the filename won't extend 15 chars.

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

    int numWMatrices = argc - 2; // Gets the number of W matrces passed on the command line.
    char *out_file[numWMatrices];
    char *err_file[numWMatrices];

    int out_fd[numWMatrices];
    int err_fd[numWMatrices];
    
    for (int i = 0; i < numWMatrices; ++i) {
        int preChild[2];
        if (pipe(preChild) == -1) {
            printf("Pipe creation failure.\n");
            return 1; 
        }

        pid_t pid = fork();
        if (pid < 0) { // fork() failure
            printf("fork() error.");
            return 1;
        } else if (pid == 0) { // Child process
            close(preChild[1]);

            int childPID = getpid();
            int out_size;
            int err_size;
            char out[FN_SIZE];
            char err[FN_SIZE];

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
            if (read(preChild[0], out, out_size) == -1) {
                printf("Read error in child pid %d, for reading stdout filename.\n", childPID);
                close(preChild[0]);
                return 1;
            }

            if (read(preChild[0], err, err_size) == -1) {
                printf("Read error in child pid %d, for reading stderr filename.\n", childPID);
                close(preChild[0]);
                return 1;
            }
            close(preChild[0]);

            // Add a null terminator at the end of the name.
            out[out_size] = '\0';
            err[err_size] = '\0';

            out_file[i] = strdup(out);
            err_file[i] = strdup(err);

            // Create the actual files on disk, open in write only and append mode, and ensure data integrity.
            out_fd[i] = open(out_file[i], O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0777);
            err_fd[i] = open(err_file[i], O_WRONLY | O_CREAT | O_APPEND | O_DSYNC, 0777);

            // Redirect stdout and stderr to out_file and err_file respectively.
            dup2(out_fd[i], STDOUT_FILENO);
            dup2(err_fd[i], STDERR_FILENO);

            int matrixNum = argc - (numWMatrices - i); // Gets the index of the W matrix to pass.
            fprintf(stdout, "Starting command %d: child %d pid of parent %d\n", i + 1, childPID, getppid());
            fflush(stdout); // Ensure that any pending writes have been written.

            char *args[] = {"matrixmult_parallel", argv[1], argv[matrixNum], out_file[i], err_file[i], NULL};
            // Call matrixmult with the A matrix and a W matrix specified by the index.
            if (execv("./matrixmult_parallel.o", args) == -1) {

                fprintf(stderr, "execv() failed. Command tried to execute: %s %s %s %s %s\n", 
                        "./matrixmult_parallel.o", args[1], args[2], args[3], args[4]);
                close(out_fd[i]);
                close(err_fd[i]);
                return 1;
            }
        } else { // Parent process
            close(preChild[0]);
            
            char out[FN_SIZE];
            char err[FN_SIZE];

            // Create a string that results in PID.out and PID.err, where PID is the PID of the 
            // process, and store that in the char array out_file and err_file respectively.
            int out_size = snprintf(out, sizeof(out), "%d.out", pid);
            int err_size = snprintf(err, sizeof(err), "%d.err", pid);

            // Add a null terminator at the end of the name.
            out[out_size] = '\0';
            err[err_size] = '\0';

            out_file[i] = strdup(out);
            err_file[i] = strdup(err);

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
            if (write(preChild[1], out_file[i], out_size) == -1) {
                printf("Write error for sending filename %s to child pid %d.\n", out_file[i], pid);
                close(preChild[1]);
                return 1;
            }

            // Give the name of the err_file to the child process.
            if (write(preChild[1], err_file[i], err_size) == -1) {
                printf("Write error for sending filename %s to child pid %d.\n", err_file[i], pid);
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
        out_fd[i] = open(out_file[i], O_WRONLY | O_APPEND | O_DSYNC, 0777);
        err_fd[i] = open(err_file[i], O_WRONLY | O_APPEND | O_DSYNC, 0777);

        // Redirect stdout and stderr to out_file and err_file respectively.
        dup2(out_fd[i], STDOUT_FILENO);
        dup2(err_fd[i], STDERR_FILENO);

        fprintf(stdout, "Finished child %d pid of parent %d\n", childPID, getpid());

        if (WIFEXITED(wstatus)) { // Check if the child process exited normally.
            int exitStatus = WEXITSTATUS(wstatus); // Store exit code of child process.

            if (exitStatus == 0) { // If the child process exited with code 0 (success)
                fprintf(stdout, "Exited with exitcode = %d\n", exitStatus);
            } else {
                fprintf(stderr, "Exited with exitcode = %d\n", exitStatus);
            }
        } else if (WIFSIGNALED(wstatus)) {
            fprintf(stderr, "Killed with signal %d\n", WTERMSIG(wstatus));
        }

        fflush(stdout);
        fflush(stderr);

        close(out_fd[i]);
        close(err_fd[i]);
    }

    return 0;
}
