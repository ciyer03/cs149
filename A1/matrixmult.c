/**
 * Description: This program allows the user to multiply 3 matrices:
 * A, W, and B, or specific sizes. A, the input matrix, will be of 
 * size 1x3, W, the weights matrix, will be of size 3x5, and B, the 
 * bias matrix, will be of size 1x5. The resultant matrix, R, will 
 * be of size 1x5 as well.
 * Author names: Chandramouli Iyer 
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: September 8th
 * Creation date: September 8th
 **/

#include <stdio.h>
#include <stdlib.h>

// Function prototypes. See the function declarations for more information.
void zeroOut(int*, int, int);
void fillMatrix(int*, int, int, FILE);
void dotProduct(int*, int*, int*);

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
    if (argc != 4) {
        printf("error: expecting exactly 3 files as input\n");
        printf("Terminating, exit code 1.\n");
        return 1;
    }

    // Create FILE pointers for the given files, and open in read mode.
    FILE *A = fopen(argv[1], "r");
    FILE *W = fopen(argv[2], "r");
    FILE *B = fopen(argv[3], "r");

    // Check for invalid inputs and exit if found.
    if (A == NULL || W == NULL || B == NULL) {
        if (A == NULL) {
            printf("error: cannot open file %s\n", argv[1]);
        }
        
        if (W == NULL) {
            printf("error: cannot open file %s\n", argv[2]);
        }

        if (B == NULL) {
            printf("error: cannot open file %s\n", argv[3]);
        }

        printf("Terminating, exit code 1.\n");
        return 1; 
    }

    int input[3]; // Matrix of size 1x3. The input matrix.
    int weights[3][5]; // Matrix of size 3x5 The weights matrix.
    int product[5]; // Matrix of size 1x5. Stores the dot product of A and W.
    int bias[5]; // Matrix of size 1x5. The bias matrix.
    int resultant[5]; // Matrix of size 1x5. Stores the resultant matrix.

    fclose(A);
    fclose(W);
    fclose(B);
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
    int product; // Gets the (memory) length of the matrix.

    // Checks if the number of rows is zero (i.e. 1D array) or not.
    if (rows != 0) {
        product = rows * columns; // If not, multiplies the rows and columns to get 
        // the memory length.
    } else {
        product = columns; // If zero, it's a 1D array and spans the column length.
    }

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
 * taken from the provided file.
 *
 * Assumption: The provided file and matrix must exist already. The matrix must have 
 * the same size as the rows and columns.
 *
 * Input parameters: matrix: The matrix in which the values will be stored.
 *                   rows: The number of rows in the matrix to be filled.
 *                   columns: The number of columns in the matrix to be filled.
 *                   file: The file that contains the values to be filled.
 * Returns: Nothing.
 **/
void fillMatrix(int* matrix, int rows, int columns, FILE file) {

}

/**
 * Calculates the dot product of two given matrices and stores the result in another
 * provided matrix.
 *
 * Assumption: matrix1 has a size of 1x3, and matrix2 has a size of 3x5. All matrices 
 * must be provided as arguments, including the one in which the result will be stored.
 *
 * Input parameters: matrix1: Matrix with the size 1x3.
 *                   matrix2: Matrix with the size 3x5.
 *                   product: Matrix in which the dot product will be stored. Must be of
 *                   size 1x5.
 *
 * Returns: Nothing.
**/
void dotProduct(int* matrix1, int* matrix2, int* product) {

}
