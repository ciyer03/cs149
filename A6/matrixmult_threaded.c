/**
 * Description: This program multiplies two 8x8 matrices, the first two of
 * which are provided as CLI args. It appends the result to a dynamically
 * allocated array. Them, it accepts more A matrices from the parent process.
 * It multiplies that matrix and the second matrix that has been provided in
 * the CLI args, the result of which is also appended to the dynamically
 * allocated array. This array will be automatically expanded as needed.
 * Once all the matrices have been passed by the parent and the subsequent
 * result has been calculated and appended, the contents of the appended
 * matrix will be written to a file PID.out, where PID is the PID of this
 * process. The whole matrix multiplication process is done using multiple
 * threads to achieve this a faster way.
 *
 * Author names: Chandramouli Iyer, Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu, safiullah.saif@sjsu.edu
 * Last modified date: December 6th
 * Creation date: November 30th
 **/

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COLUMNS 8
#define MAX_ROWS 8
#define MAX_PROCESSES 8
#define PRODUCT (MAX_ROWS * MAX_COLUMNS)
#define THREAD_NUM 64

int input[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8. The input matrix.
int weights[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8 The weights matrix.
int* finalResultantMatrix;
int matrixSize;
pthread_mutex_t writeToRMutex;

void fillMatrix(int* resultantMatrix, const int rows, const int columns,
    FILE* file);
int calcResult(const int* aMatrix, const int* wMatrix, int* result);
void* doMatrixMult(void* args);
int readAMatrix();
void appendToResultant(int* tempResult);
void rowSum(const int* matrix1, const int* matrix2, int* product, const int row,
    const int column);
void fillRow(const int row, const int* sourceMatrix, int* resultant);
int closeAll(FILE* A, FILE* W, int* toFreeArray, pthread_mutex_t* mutex);
void printArr(const int* resultant, const int size);

typedef struct MatrixData {
    const int* aMatrix;
    const int* wMatrix;
    int* result;
    int cell;
} MatrixData;

int main(int argc, char* argv[])
{

    // Checks if there are exactly five arguments (2 files, real STDOUT_FILENO,
    // and 1 default).
    if (argc != 4) {
        fprintf(stderr, "error: expecting exactly 3 inputs.\n");
        fprintf(stderr, "Terminating, exit code 1.\n");
        fflush(stderr);
        exit(1);
    }

    // Create FILE pointers for the given files, and open in read and append
    // modes, as needed.
    FILE* A = fopen(argv[1], "r");
    FILE* W = fopen(argv[2], "r");

    // Check for invalid inputs and exit if found.
    if (A == NULL || W == NULL) {
        if (A == NULL) {
            fprintf(stderr, "error: cannot open file %s\n", argv[1]);
        }

        if (W == NULL) {
            fprintf(stderr, "error: cannot open file %s\n", argv[2]);
        }

        fprintf(stderr, "Terminating, exit code 1.\n");
        exit(closeAll(A, W, finalResultantMatrix, NULL));
    }

    fillMatrix(&(input[0][0]), MAX_ROWS, MAX_COLUMNS, A);
    fillMatrix(&(weights[0][0]), MAX_ROWS, MAX_COLUMNS, W);

    finalResultantMatrix = (int*)malloc(PRODUCT * sizeof(int));
    if (finalResultantMatrix == NULL) {
        fprintf(stderr,
            "Memory allocation failed. Refer to prior messages for exact "
            "details. A matrix %s, W matrix %s.",
            argv[1], argv[2]);
        exit(closeAll(A, W, finalResultantMatrix, NULL));
    }
    matrixSize += PRODUCT;

    pthread_mutex_init(&writeToRMutex, NULL);
    if (calcResult(&(input[0][0]), &(weights[0][0]), finalResultantMatrix) == 1) {
        fprintf(stderr, "Matrix Multiplication with CLI args failed.\n");
        exit(closeAll(A, W, finalResultantMatrix, &writeToRMutex));
    }

    if (readAMatrix() == 1) {
        fprintf(stderr, "Matrix Multiplication with passed in A matrix failed.\n");
        exit(closeAll(A, W, finalResultantMatrix, &writeToRMutex));
    }
    pthread_mutex_destroy(&writeToRMutex);

    fprintf(stdout, "A = %s\n", argv[1]);
    fprintf(stdout, "W = %s\n", argv[2]);
    fprintf(stdout, "R = [ \n");
    printArr(finalResultantMatrix, matrixSize);
    free(finalResultantMatrix);

    // Flush stdout and stderr to their respective file descriptors immediately.
    fflush(stdout);
    fflush(stderr);

    // Reset stdout to the terminal
    if (dup2(atoi(argv[3]), STDOUT_FILENO) == -1) {
        fprintf(stderr, "Error redirecting stdout to terminal.\n");
        exit(closeAll(A, W, finalResultantMatrix, NULL));
    }

    // Close the files after use to prevent memory leaks.
    fclose(A);
    fclose(W);

    return 0;
}

/**
 * Fills the given matrix with the appropriate number of rows and columns with
 * values taken from the provided file. Look at the header comments of the
 * zeroOut() function to understand why a pointer is being passed instead of an
 * array.
 *
 * @attention The provided file must exist. The matrix must have the same size
 *as the rows and columns. Row and column values are not malicious. Not reading
 *more than 60 characters at a time.
 *
 * @param matrix: The matrix in which the values will be stored.
 * @param rows: The number of rows in the matrix to be filled.
 * @param columns: The number of columns in the matrix to be filled.
 * @param file: The file that contains the values to be filled.
 *
 **/
void fillMatrix(int* resultantMatrix, const int rows, const int columns,
    FILE* file)
{
    const int product = rows * columns;
    int* preOp = resultantMatrix; // Store the memory address of matrix prior to
    // manipulation.
    int index = 0; // Tracks how far into valid memory we are in.

    char line[500]; // Assuming we won't read in more than 500 characters at a
    // time.

    // Index must be less than product for the program to be in valid memory range
    // for modification. Also check if we haven't already reached EOF.
    while (index < product && (!feof(file))) {
        // Only get in if the line isn't NULL.
        if (fgets(line, sizeof(line), file) != NULL) {

            // Check if the last character of the string is actually a newline,
            // because in certain cases the last character may actually not be a
            // newline, which will result in an overwrite of an actual value.
            if (line[strlen(line) - 1] == '\n') {
                line[strlen(line) - 1] = '\0'; // Get rid of newline character.
            }

            char* fetch = strtok(line, " "); // Read in a number. They are separated
            // by spaces in the file.

            // Keeps track of how many columns have been traversed. Required so that
            // if there are less numbers taken in than there are columns, we can move
            // the pointer to end of the row.
            int columnCounter = columns;

            // Validate we haven't reach end of line or other errors, and are still in
            // valid memory range.
            while (fetch != NULL && index < product) {
                columnCounter--;
                int number = atoi(fetch); // Convert the read in character into a numeral.
                *(resultantMatrix) = number; // Store the numeral at the memory address.
                resultantMatrix++; // Increment to the next memory address of the array.
                // Valid
                // increments are OS specific and will be handled by compiler.
                index++; // Increment the valid memory validator.
                fetch = strtok(NULL, " "); // Read in the next numeral.
            }
            resultantMatrix += columnCounter;
        }
    }

    // Check if the resultantMatrix pointer has been incremented. If so, return
    // the pointer to its valid memory location (i.e start of the array.).
    if (resultantMatrix > preOp) {
        resultantMatrix = preOp;
    }
}

/**
 * Calculates and write the matrix multiplication of aMatrix * wMatrix to
 *result.
 *
 * @attention Assumes that aMatrix, wMatrix, and result matrices are all 8x8 in
 *size.
 *
 * @param aMatrix The first matrix.
 * @param wMatrix The second matrix.
 * @param result The matrix into which to store the result of aMatrix * wMatrix.
 *
 * @return 1 on error, 0 on success
 *
 **/
int calcResult(const int* aMatrix, const int* wMatrix, int* result)
{
    pthread_t cells[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; ++i) {
        MatrixData* md = (MatrixData*)malloc(sizeof(MatrixData));
        md->aMatrix = aMatrix;
        md->wMatrix = wMatrix;
        md->result = result;
        md->cell = i;

        if (pthread_create(&cells[i], NULL, &doMatrixMult, md) != 0) {
            fprintf(stderr, "Error while creating thread %d\n", i);
            free(md);
            return 1;
        }
    }

    for (int i = 0; i < THREAD_NUM; ++i) {
        if (pthread_join(cells[i], NULL) != 0) {
            fprintf(stderr, "Error while waiting for thread %d\n", i);
            return 1;
        }
    }

    return 0;
}

/**
 * Multiplies the first matrix and the second matrix in a parallel manner.
 *
 * @param args a dynamically allocated array containing the A, W, Result, and
 *index variables.
 *
 * @return 1 on error, and 0 on successful run
 **/
void* doMatrixMult(void* args) {

}

/**
 * Calculates one cell of the product matrix, by mutiplying the given row with
 *the given column and storing it in its respective cell in product
 *
 * @attention matrix1 and matrix 2 have a size of 8x8.
 *
 * @param matrix1 Matrix with the size 8x8.
 * @param matrix2 Matrix with the size 8x8.
 * @param product Matrix in which the dot product will be stored.
 * @param row The row to multiply
 * @param column The column to multiply
 *
 **/
void rowSum(const int* matrix1, const int* matrix2, int* product, const int row,
    const int column)
{
    // Calculates the row to be multiplied.
    const int rowStart = row * MAX_ROWS;
    int result = 0;

    // Loop calculates single row and single column multiplication.
    for (int i = 0; i < MAX_ROWS; ++i) {
        const int rowIncrement = rowStart + i;
        const int columnIncrement = (i * MAX_COLUMNS) + column;
        result += (*(matrix1 + rowIncrement)) * (*(matrix2 + columnIncrement));
    }

    const int cell = rowStart + column; // Which cell to write the result to

    pthread_mutex_lock(&writeToRMutex);
    *(product + cell) = result;
    pthread_mutex_unlock(&writeToRMutex);

    return;
}

/**
 * Reads passed in A matrix from the parent, creates an array out of it, and
 *does matrix multiplication with the passed in A matrix and the previously
 *passed in W matrix.
 *
 **/
int readAMatrix()
{
    while (1) {
        size_t bufferLen;

        if (read(STDIN_FILENO, &bufferLen, sizeof(size_t)) == 0) {
            break;
        }

        if (bufferLen == 0) {
            break;
        }

        char aMatrixFile[bufferLen + 1];

        if (read(STDIN_FILENO, aMatrixFile, bufferLen) == -1) {
            fprintf(stderr, "Error copying A matrix filename from pipe.\n");
            return 1;
        }

        aMatrixFile[bufferLen] = '\0';

        FILE* aMatrix = fopen(aMatrixFile, "r");
        if (aMatrix == NULL) {
            fprintf(stderr, "error: cannot open file %s read in from stdin\n",
                aMatrixFile);
            fprintf(stderr, "Terminating, exit code 1.\n");
            return 1;
        }

        int tempA[MAX_ROWS][MAX_COLUMNS];
        memset(tempA, 0, sizeof(int) * (MAX_ROWS * MAX_COLUMNS));

        fillMatrix(&(tempA[0][0]), MAX_ROWS, MAX_COLUMNS, aMatrix);

        matrixSize += PRODUCT;
        int* tempResultArray = (int*)realloc(finalResultantMatrix, matrixSize * sizeof(int));
        if (tempResultArray == NULL) {
            fprintf(stderr, "realloc() failed for matrix %s.", aMatrixFile);
            matrixSize -= PRODUCT;
            return 1;
        }
        finalResultantMatrix = tempResultArray;

        if ((calcResult(&(tempA[0][0]), &(weights[0][0]),
                (finalResultantMatrix + (matrixSize - PRODUCT))))
            == 1) {
            fprintf(stderr, "Matrix Multiplication with stdin args failed.\n");
            return 1;
        }
    }

    return 0;
}

/**
 * Flushes stdout and stderr, and then closes the passed in files.
 *
 * @param A The input file to be closed.
 * @param W The weights file to be closed.
 * @param toFreeArray The dynamically allocated array to be freed.
 *
 * @return
 *
 **/
int closeAll(FILE* A, FILE* W, int* toFreeArray, pthread_mutex_t* mutex)
{
    fflush(stdout);
    fflush(stderr);

    // Close the files after use to prevent memory leaks.
    if (A == NULL || W == NULL) {
        if (A != NULL) {
            fclose(A);
        }

        if (W != NULL) {
            fclose(W);
        }
    }

    // Free allocated memory
    if (toFreeArray != NULL) {
        free(toFreeArray);
        toFreeArray = NULL;
    }

    // Destroy resources allocated for the mutex
    if (mutex != NULL) {
        pthread_mutex_destroy(mutex);
    }

    return 1;
}

/**
 * Prints the contens of the given array.
 *
 * @attention: The size of the array is less than or equal to the given value.
 *
 * @param resultant The array whose values are to be printed.
 * @param size Size of the array.
 **/
void printArr(const int* resultant, const int size)
{
    for (int i = 0; i < size; ++i) {
        if ((i != 0) && (i % MAX_COLUMNS == 0)) {
            fprintf(stdout, "\n");
        }
        fprintf(stdout, "%d ", *(resultant + i));
    }
    fprintf(stdout, "]\n");
}
