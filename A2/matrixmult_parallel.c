/**
 * Description: This program multiplies two 8x8 matrices, and prints out the matrix to 
 * stdout. It uses multiple child processes to achieve this a faster way.
 * Author names: Chandramouli Iyer 
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: September 23rd
 * Creation date: September 23rd
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COLUMNS 8
#define MAX_ROWS 8
#define MAX_PROCESSES 8


// Function prototypes. See the function declarations for more information.
void zeroOut(int *matrix, int rows, int columns);
void fillMatrix(int* matrix, int rows, int columns, FILE *file);
void rowSum(int* matrix1, int* matrix2, int* product, int row);
void printArr(int *matrix, int rows, int columns);
void makeResult(int *matrix1, int *matrix2, int *resultant);
void fillRow(int row, int *sourceMatrix, int *resultant);

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
int main(int argc, char *argv[])
{
    // Checks if there are exactly four arguments (3 files, and 1 default).
    if (argc != 3) {
        printf("error: expecting exactly 2 files as input\n");
        printf("Terminating, exit code 1.\n");
        return 1;
    }

    // Create FILE pointers for the given files, and open in read mode.
    FILE *A = fopen(argv[1], "r");
    FILE *W = fopen(argv[2], "r");

    // Check for invalid inputs and exit if found.
    if (A == NULL || W == NULL) {
        if (A == NULL) {
            printf("error: cannot open file %s\n", argv[1]);
        }

        if (W == NULL) {
            printf("error: cannot open file %s\n", argv[2]);
        }

        printf("Terminating, exit code 1.\n");
        return 1; 
    }

    int input[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8. The input matrix.
    int weights[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8 The weights matrix.

    zeroOut(&(input[0][0]), MAX_ROWS, MAX_COLUMNS);
    zeroOut(&(weights[0][0]), MAX_ROWS, MAX_COLUMNS);

    fillMatrix(&(input[0][0]), MAX_ROWS, MAX_COLUMNS, A);
    fillMatrix(&(weights[0][0]), MAX_ROWS, MAX_COLUMNS, W);

    int resultant[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8. The resultant matrix.

    int fd[MAX_PROCESSES][2];

    // Create pipes for read/write for all processes.
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        if (pipe(fd[i]) == -1) { // pipe() returns -1 on error.
            printf("Error creating pipes.\n");
            return 1;
        }
    }
    
    pid_t pid[MAX_PROCESSES]; // Hold PIDs for each child process.

    for (int i = 0; i < MAX_PROCESSES; ++i) {
        pid[i] = fork();
    }

    // Parent process.
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        int wstatus;
        int childPID = wait(&wstatus);
        if (WIFEXITED(wstatus)) { // If the child process exited normally.
            int exitStatus = WEXITSTATUS(wstatus);
            if (exitStatus == 0) { // If the child process exited with code 0 (success)
                
                // Holds the row values returned by the child process.
                int rowResult[MAX_COLUMNS];

                int rowCompleted; // The row that the child process calculated.

                // Reads in the row that the row that the child process calculated.
                if (read(fd[MAX_PROCESSES][0], &rowCompleted, sizeof(int)) == -1) {
                    printf("Error while reading value. Problematic child: %d\n", 
                           childPID);
                    return 1;
                }

                // Reads in the row values that the child process calculated.
                if (read(fd[MAX_PROCESSES][0], &rowResult, sizeof(int) * MAX_COLUMNS)
                    == -1) {
                    printf("Error while reading value. Problematic child: %d\n", 
                           childPID);
                    return 1;
                }
                
                fillRow(rowCompleted, rowResult, &(resultant[0][0]));

            } else {
                printf("Child %d exited abnormally with code %d.\n", childPID, 
                       exitStatus);
            }
        }
    }
    
    printf("Result of %s*%s is = ", argv[1], argv[2]);
    printArr(&(resultant[0][0]), MAX_ROWS, MAX_COLUMNS);

    // Close the files after use to prevent memory leaks.
    fclose(A);
    fclose(W);
    return 0;
}

/**
 * Zeroes out the provided number of rows and columns in the given matrix. We take in 
 * the matrix as a pointer to take advantage of the fact that while declaring arrays, 
 * the OS allocates memory contiguously, and also the fact that the number of bytes 
 * allocated for an integer is consistent on the operating system. To iterate through 
 * the entire array, we only need to increment the matrix pointer by one (pointer 
 * arithmetic). To access the element at that memory address (remember we are dealing 
 * with pointers), just dereference the pointer. The advantage of this is that we don't
 * need to declare separate functions in order to handle different types of arrays. 
 * You can theoretically pass in a 1D or a 10D array and the logic will still work.
 *
 * The disadvantage is that the process is sequential, full (i.e. the entire row/column
 * will be zeroed out), and, currently, there are no protections against faulty values 
 * for rows and columns, so theoretically you can zero out memory that doesn't belong to
 * you and/or crash the program.
 *
 * Assumption: The given matrix exists and has at least the number of rows and columns
 * provided. Also that the number of rows and columns are not malicious.
 * 
 * Input parameters: matrix: The matrix to be zeroed out.
 *                   rows: The number of rows to zero out.
 *                   columns: The number of columns to zero out.
 *
 * Returns: Nothing.
 **/
void zeroOut(int *matrix, int rows, int columns) {
    const int product = rows * columns; // Used to calculate the valid memory range of the matrix.
    // Iterate through the memory length (determined by product).
    for (int i = 0; i < product; ++i) {
        *(matrix) = 0; // Dereference the pointer, and zero it out.

        // Increment the memory address by one. The compiler will determine 
        // the correct step for the memory address depending on the amount of space 
        // allocated for an integer on that specific machine.
        matrix++;
    }
    matrix -= product; // Return the pointer to the mem address of start of the array.
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
void fillMatrix(int* matrix, int rows, int columns, FILE *file) {

    const int product = rows * columns; 
    int *preOp = matrix; // Store the memory address of matrix prior to manipulation.
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
void rowSum(int* matrix1, int* matrix2, int* product, int row) {
    // Calculates the row to be multiplied.
    int rowStart = (row - 1 ) * MAX_ROWS;

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
            int rowIncrement = rowStart + j;
            int columnIncrement = (j * MAX_COLUMNS) + i;
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
 *
 *
 **/
void fillRow(int row, int *sourceMatrix, int *resultant) {

}


/**
 * Prints the contents of the given matrix. Since we are using pointers, we calculate 
 * the valid memory range using the numbers of rows and columns.
 *
 * Assumptions: The rows and columns variables are not a malicious, and represent the 
 * actual number of rows and columns in the matrix.
 *
 * Input parameters: matrix: The array pointer.
 *                   rows: The number of rows in the matrix.
 *                   columns: The number of columns in the matrix.
 **/
void printArr(int *matrix, int rows, int columns) {
    const int product = rows * columns; // Used to calculate the valid memory range of the matix.

    printf("[ ");

    // Iterates through the array addresses, derefernces the pointer, and prints out the
    // value at that address. Then increments the pointer addresses to the next value.
    for (int i = 0; i < product; ++i) {
        printf("%d ", *(matrix));
        matrix++;
    }
    printf("]\n");
    matrix -= product; // Set the pointer back to the start of the array.
}

/**
* Adds the product matrix to the bias matrix, and stores it in the
* resultant matrix. the formula for the resultant matrix
* is given as follows: resultant = product + bias, where product = A * W.
**/
void makeResult(int *matrix1, int *matrix2, int *resultant) {
    const int maxSize = 5;
    for (int i = 0; i < maxSize; ++i) {
        *(resultant + i) = (*(matrix1 + i) + *(matrix2 + i));
    }
}
