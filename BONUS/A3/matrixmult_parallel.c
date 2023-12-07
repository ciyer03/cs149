/**
 * Description: This program multiplies two 8x8 matrices, and prints out the matrix to 
 * stdout. It uses multiple child processes to achieve this a faster way.
 * Author names: Chandramouli Iyer
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: December 6th
 * Creation date: December 6th
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COLUMNS 8
#define MAX_ROWS 8
#define MAX_PROCESSES 8

double input[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8. The input matrix.
double weights[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8 The weights matrix.
double resultant[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8. The resultant matrix.

// Function prototypes. See the function declarations for more information.
void fillMatrix(double * matrix, const int rows, const int columns, FILE *file);
void rowSum(const double *matrix1, const double *matrix2, double *product, const int row);
void fillRow(const int row, const double *sourceMatrix, double *resultant);
void printArr(double *matrix, const int rows, const int columns);

int main(int argc, char *argv[])
{
    // Checks if there are exactly five arguments (4 files, and 1 default).
    if (argc != 5) {
        fprintf(stderr, "error: expecting exactly 5 inputs.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        fflush(stderr);
        return 1;
    }

    // Create FILE pointers for the given files, and open in read and append modes, as needed.
    FILE *A = fopen(argv[1], "r");
    FILE *W = fopen(argv[2], "r");
    FILE *out_file = fopen(argv[3], "a");
    FILE *err_file = fopen(argv[4], "a");

    // Check for invalid inputs and exit if found.
    if (A == NULL || W == NULL || out_file == NULL || err_file == NULL) {
        if (A == NULL) {
            fprintf(stderr, "error: cannot open file %s\n", argv[1]);
        }

        if (W == NULL) {
            fprintf(stderr, "error: cannot open file %s\n", argv[2]);
        }

        if (out_file == NULL) {
            fprintf(stderr, "error: cannot open file %s\n", argv[3]);
        }

        if (err_file == NULL) {
            fprintf(stderr, "error: cannot open file %s\n", argv[4]);
        }

        fprintf(stderr, "Terminating, exit code 1.\n");
        fflush(stderr);
        return 1;
    }

    fillMatrix(&(input[0][0]), MAX_ROWS, MAX_COLUMNS, A);
    fillMatrix(&(weights[0][0]), MAX_ROWS, MAX_COLUMNS, W);

    // Create a read/write pipe for each child process.
    int fd[MAX_PROCESSES][2];

    // Create pipes for read/write for all processes.
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        if (pipe(fd[i]) == -1) { // pipe() returns -1 on error.
            fprintf(stderr, "Error creating pipes.\n");
            fflush(stderr);
            return 1;
        }
    }

    // Calculate dot product of each row of the matrix in a different child process.
    for (int i = 0; i < MAX_PROCESSES; ++i) {

        // Store the PID of each process. Will be 0 for child process. In the parent 
        // process, it'll the PID of the child process.
        pid_t pid = fork();

        if (pid == 0) { // If we are in the child process.

            // Close unneeded read and write ends of the pipe.
            for (int j = 0; j < MAX_PROCESSES; ++j) {
                close(fd[j][0]); // Child processes won't read anything.
                if (j != i) {
                    close(fd[j][1]); // Close all write ends except the current.
                }
            }

            // Pass the row number to the parent process, and if for some reason that
            // fails, end the process.
            if (write(fd[i][1], &i, sizeof(int)) == -1) {
                fprintf(stderr, "Error while writing row number. Problematic child: %d. Iteration: %d.\n",
                        getpid(), i);
                fflush(stderr);
                return 1;
            }

            // Calculate and store the row specific dot product.
            double rowResult[MAX_COLUMNS];  
            rowSum(&(input[0][0]), &(weights[0][0]), rowResult, i);

            // Pass the calculated array to the parent process, and if for some reason 
            // that fails, end the process.
            if (write(fd[i][1], rowResult, sizeof(double) * MAX_COLUMNS) == -1) {
                fprintf(stderr, "Error while writing array. Problematic child: %d. Iteration: %d.\n",
                        getpid(), i);
                fflush(stderr);
                return 1;
            }

            close(fd[i][1]); // Close write pipe once written.
            return 0; // End the child process so it doesn't fork itself.
        }
    }

    // Parent process.
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        int wstatus;
        int childPID = wait(&wstatus); // Wait for each child process to end.
        if (WIFEXITED(wstatus)) { // Check if the child process exited normally.
            int exitStatus = WEXITSTATUS(wstatus); // Store exit code of child process.
            if (exitStatus == 0) { // If the child process exited with code 0 (success)
                // Holds the row values returned by the child process.
                double rowResult[MAX_COLUMNS];

                int rowCompleted; // The row that the child process calculated.

                // Reads in the row that the child process calculated.
                if (read(fd[i][0], &rowCompleted, sizeof(int)) == -1) {
                    fprintf(stderr, "Error while reading value. Problematic child: %d\n", childPID);
                fflush(stderr);
                    return 1;
                }

                // Reads in the row values that the child process calculated.
                if (read(fd[i][0], rowResult, sizeof(double) * MAX_COLUMNS) == -1) {
                    fprintf(stderr, "Error while reading value. Problematic child: %d\n", childPID);
                fflush(stderr);
                    return 1;
                }

                close(fd[i][0]); // Close the read pipe after use.
                fillRow(rowCompleted, rowResult, &(resultant[0][0]));

            } else { // In case the child process failed.
                fprintf(stderr, "Child %d exited abnormally with code %d.\n", childPID, exitStatus);
                fflush(stderr);
                return 1;
            }
        }
    }

    fprintf(stdout, "%s=[", argv[1]);
    printArr(&(input[0][0]), MAX_ROWS, MAX_COLUMNS);
    fprintf(stdout, "%s=[", argv[2]);
    printArr(&(weights[0][0]), MAX_ROWS, MAX_COLUMNS);
    fprintf(stdout, "R=[");
    printArr(&(resultant[0][0]), MAX_ROWS, MAX_COLUMNS);

    // Flush stdout and stderr to their respectively file descriptors immediately.
    fflush(stdout);
    fflush(stderr);

    // Close the files after use to prevent memory leaks.
    fclose(A);
    fclose(W);
    fclose(out_file);
    fclose(err_file);

    return 0;
}

/**
 * Fills the given matrix with the appropriate number of rows and columns with values 
 * taken from the provided file. Look at the header comments of the zeroOut() function
 * to understand why a pointer is being passed instead of an array.
 *
 * Assumption: The provided file and matrix must exist already. The matrix must have 
 * the same size as the rows and columns. Row and column values are not malicious. Not 
 * reading more than 60 characters at a time.
 *
 * Input parameters: matrix: The matrix in which the values will be stored.
 *                   rows: The number of rows in the matrix to be filled.
 *                   columns: The number of columns in the matrix to be filled.
 *                   file: The file that contains the values to be filled.
 * Returns: Nothing.
 **/
void fillMatrix(double *matrix, const int rows, const int columns, FILE *file) {

    const int product = rows * columns; 
    double *preOp = matrix; // Store the memory address of matrix prior to manipulation.
    int index = 0; // Tracks how far into valid memory we are in.

    char line[100]; // Assuming we won't read in more than 100 characters at a time.

    // Index must be less than product for the program to be in valid memory range for 
    // modification. Also check if we haven't already reached EOF.
    while (index < product && (!feof(file))) {
        // Keeps track of how many columns have been traversed. Required so that if 
        // there are less numbers taken in than there are columns, we can move the 
        // pointer to end of the row.
        int columnCounter = columns;
        // Only get in if the line isn't NULL.
        if (fgets(line, sizeof(line), file) != NULL) {

            // Check if the last character of the string is actually a newline, because 
            // in certain cases the last character may actually not be a newline, which 
            // will result in an overwrite of an actual value.
            if (line[strlen(line) - 1] == '\n') {
                line[strlen(line) - 1] = '\0'; // Get rid of newline character.
            }

            char *fetch = strtok(line, " "); // Read in a number. They are separated 
            // by spaces in the file.
            int number; // For storing the read in number.

            // Validate we haven't reach end of line or other errors, and are still in
            // valid memory range.
            while (fetch != NULL && index < product) {
                columnCounter--;
                number = atoi(fetch); // Convert the read in character into a numeral.
                *(matrix) = number; // Store the numeral at the memory address.
                matrix++; // Increment to the next memory address of the array. Valid 
                // increments are OS specific and will be handled by compiler.
                index++; // Increment the valid memory validator.
                fetch = strtok(NULL, " "); // Read in the next numeral.
            }
            matrix += columnCounter;
        }
    }

    // Check if the matrix pointer has been incremented. If so, return the pointer to 
    // its valid memory location (i.e start of the array.).
    if (matrix > preOp) { 
        matrix = preOp;
    }
}

/**
 * Calculates the dot product of the specified row in matrix1 with the entirety of 
 * matrix2, and stores the result in the product result.
 *
 * Assumption: matrix1 and matrix 2 have a size of 8x8, and the product matrix has a 
 * size of 1x8.
 *
 * Input parameters: matrix1: Matrix with the size 8x8.
 *                   matrix2: Matrix with the size 8x8.
 *                   product: Matrix in which the dot product will be stored. Must be of
 *                   size 1x8.
 *
 * Returns: Nothing.
**/ 
void rowSum(const double *matrix1, const double *matrix2, double *product, const int row) {
    // Calculates the row to be multiplied.
    const int rowStart = row * MAX_ROWS;

    // Loop calculates the dot product of matrix1 and matrix2, and stores the result 
    // in product.
    for (int i = 0; i < MAX_COLUMNS; ++i) {
        // Stores the result of multiplication of the entire row and column.
        int result = 0;

        // Loop calculates single row and single column multiplication.
        for (int j = 0; j < MAX_ROWS; ++j) {

            /** 
             * Multiplies one row and one column and stores the output in result.
             * For the first value, we add the row increment with rowStart to both, get
             * to the appropriate row for multiplication and to the corresponding row 
             * position. By dereferencing that address, we get the raw value.
             *
             * For the second value we get the correct address for dereferencing by 
             * multiplying the row increment, j, with the constant weight increment of
             * 8 (calculated according to column width), so that we always land at the 
             * appropriate next value in the column. Then we add the column increment,
             * i, to the multiplied value to shift to the appropriate column for 
             * multiplication. Lastly, after we get the correct pointer offset, we add 
             * that to the pointer address, and dereference it to get the correct raw 
             * value.
             **/
            const int rowIncrement = rowStart + j;
            const int columnIncrement = (j * MAX_COLUMNS) + i;
            result += (*(matrix1 + rowIncrement)) * (*(matrix2 + columnIncrement));
        }

        /** Store the calculated result in the appropriate dereferenced column 
          * (offset calculated with the pointer address plus column increment, i) in the
          * product array.
          **/
        *(product + i) = result;
    }
}

/**
 * Fills the specified row in the resultant matrix with the values from the source
 * matrix.
 *
 * Assumption: The row parameter is a valid row index (0 to 7).
 *
 * Input parameters: row: The row index in the resultant matrix to be filled.
 *                   sourceMatrix: The matrix containing the values to be copied from.
 *                   resultant: The resultant matrix to be filled.
 *
 * Returns: Nothing.
 **/
void fillRow(const int row, const double *sourceMatrix, double *resultant) {
    const int rowStart = row * MAX_ROWS;

    for (int i = 0; i < MAX_COLUMNS; ++i) {
        *(resultant + (rowStart + i)) = *(sourceMatrix + i);
    }
}

/**
 * Prints the matrix with the specified number of rows and columns in the specified format to stdout.
 *
 * Assumption: The matrix parameter points to a valid matrix of size rows x columns.
 *
 * Input parameters: matrix: Pointer to the matrix to be printed.
 *                   rows: Number of rows in the matrix.
 *                   columns: Number of columns in the matrix.
 *
 * Returns: Nothing.
 **/
void printArr(double *matrix, const int rows, const int columns) {
    const int product = rows * columns;
    for (int i = 0; i < product; ++i) {
        if (i % MAX_ROWS == 0) {
            fprintf(stdout, "\n");
        }

        fprintf(stdout, "%.2f ", *(matrix + i));
    }
    fprintf(stdout, "\n]\n");
    fflush(stdout);
}
