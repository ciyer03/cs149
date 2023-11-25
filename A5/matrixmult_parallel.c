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
 * child processes to achieve this a faster way.
 *
 * Author names: Chandramouli Iyer, Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu, safiullah.saif@sjsu.edu
 * Last modified date: November 23rd
 * Creation date: October 26th
 **/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COLUMNS 8
#define MAX_ROWS 8
#define MAX_PROCESSES 8
#define PRODUCT (MAX_ROWS * MAX_COLUMNS)

int input[MAX_ROWS][MAX_COLUMNS];	// Matrix of size 8x8. The input matrix.
int weights[MAX_ROWS][MAX_COLUMNS]; // Matrix of size 8x8 The weights matrix.
int *finalResultantMatrix;
int matrixSize;

void fillMatrix(int *resultantMatrix, const int rows, const int columns, FILE *file);
int doMatrixMult(int *aMatrix, int *tempResult);
int readAMatrix();
void appendToResultant(int *tempResult);
void rowSum(const int *matrix1, const int *matrix2, int *product, const int row);
void fillRow(const int row, const int *sourceMatrix, int *resultant);
int closeAll(FILE *A, FILE *W, int *toFreeArray);
void printArr(const int *resultant, const int size);

int main(int argc, char *argv[]) {

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
	FILE *A = fopen(argv[1], "r");
	FILE *W = fopen(argv[2], "r");

	// Check for invalid inputs and exit if found.
	if (A == NULL || W == NULL) {
		if (A == NULL) {
			fprintf(stderr, "error: cannot open file %s\n", argv[1]);
		}

		if (W == NULL) {
			fprintf(stderr, "error: cannot open file %s\n", argv[2]);
		}

		fprintf(stderr, "Terminating, exit code 1.\n");
		exit(closeAll(A, W, finalResultantMatrix));
	}

	fillMatrix(&(input[0][0]), MAX_ROWS, MAX_COLUMNS, A);
	fillMatrix(&(weights[0][0]), MAX_ROWS, MAX_COLUMNS, W);

	finalResultantMatrix = (int *)malloc(PRODUCT * sizeof(int));
	if (finalResultantMatrix == NULL) {
		fprintf(stderr,
		        "Memory allocation failed. Refer to prior messages for exact "
		        "details. A matrix %s, W matrix %s.",
		        argv[1], argv[2]);
		exit(closeAll(A, W, finalResultantMatrix));
	}
	matrixSize += PRODUCT;

	int tempResultant[MAX_ROWS][MAX_COLUMNS];
	if (doMatrixMult(&(input[0][0]), &(tempResultant[0][0])) == 1) {
		fprintf(stderr, "Matrix Multiplication with CLI args failed.\n");
		exit(closeAll(A, W, finalResultantMatrix));
	}

	appendToResultant(&tempResultant[0][0]);

	if (readAMatrix() == 1) {
		fprintf(stderr, "Matrix Multiplication with passed in A matrix failed.\n");
		exit(closeAll(A, W, finalResultantMatrix));
	}

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
		exit(closeAll(A, W, finalResultantMatrix));
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
 * @attention The provided file must exist. The matrix must have the same size as
 * the rows and columns. Row and column values are not malicious. Not reading more
 * than 60 characters at a time.
 *
 * @param matrix: The matrix in which the values will be stored.
 * @param rows: The number of rows in the matrix to be filled.
 * @param columns: The number of columns in the matrix to be filled.
 * @param file: The file that contains the values to be filled.
 *
 **/
void fillMatrix(int *resultantMatrix, const int rows, const int columns, FILE *file) {
	const int product = rows * columns;
	int *preOp = resultantMatrix; // Store the memory address of matrix prior to
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

			char *fetch = strtok(line, " "); // Read in a number. They are separated
			// by spaces in the file.

			// Keeps track of how many columns have been traversed. Required so that
			// if there are less numbers taken in than there are columns, we can move
			// the pointer to end of the row.
			int columnCounter = columns;

			// Validate we haven't reach end of line or other errors, and are still in
			// valid memory range.
			while (fetch != NULL && index < product) {
				columnCounter--;
				int number = atoi(fetch);	 // Convert the read in character into a numeral.
				*(resultantMatrix) = number; // Store the numeral at the memory address.
				resultantMatrix++;			 // Increment to the next memory address of the array.
				// Valid
				// increments are OS specific and will be handled by compiler.
				index++;				   // Increment the valid memory validator.
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
 * Multiplies the first matrix and the second matrix in a parallel manner.
 *
 * @param aMatrix the input matrix
 * @param tempResult the matrix into which the result should be stored in
 *
 * @return 1 on error, and 0 on successful run
 **/
int doMatrixMult(int *aMatrix, int *tempResult) {
	// Create a read/write pipe for each child process.
	int fd[MAX_PROCESSES][2];

	// Create pipes for read/write for all processes.
	for (int i = 0; i < MAX_PROCESSES; ++i) {
		if (pipe(fd[i]) == -1) {
			// pipe() returns -1 on error.
			fprintf(stderr, "Error creating pipes.\n");
			exit(1);
		}
	}

	// Calculate dot product of each row of the matrix in a different child
	// process.
	for (int i = 0; i < MAX_PROCESSES; ++i) {

		// Store the PID of each process. Will be 0 for child process. In the parent
		// process, it'll the PID of the child process.
		pid_t pid = fork(); // Hold PIDs for each child process.

		if (pid < 0) {
			fprintf(stderr, "fork() failed.\n");
			exit(1);
		} else if (pid == 0) {
			// If we are in the child process.

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
				fprintf(stderr,
				        "Error while writing row number. Problematic child: %d. "
				        "Iteration: %d.\n",
				        getpid(), i);
				exit(1);
			}

			// Calculate and store the row specific dot product.
			int rowResult[MAX_COLUMNS];
			rowSum(aMatrix, &(weights[0][0]), rowResult, i);

			// Pass the calculated array to the parent process, and if for some reason
			// that fails, end the process.
			if (write(fd[i][1], rowResult, sizeof(int) * MAX_COLUMNS) == -1) {
				fprintf(stderr,
				        "Error while writing array. Problematic child: %d. Iteration: "
				        "%d.\n",
				        getpid(), i);
				exit(1);
			}

			close(fd[i][1]); // Close write pipe once written.
			exit(0);		 // End the child process so it doesn't fork itself.
		}
	}

	// Parent process.
	for (int i = 0; i < MAX_PROCESSES; ++i) {
		int wstatus;
		int childPID = wait(&wstatus); // Wait for each child process to end.

		if (WIFEXITED(wstatus)) {
			// Check if the child process exited normally.
			int exitStatus =
			    WEXITSTATUS(wstatus); // Store exit code of child process.
			if (exitStatus ==
			        0) {
				// If the child process exited with code 0 (success)
				// Holds the row values returned by the child process.
				int rowResult[MAX_COLUMNS];

				int rowCompleted; // The row that the child process calculated.

				// Reads in the row that the child process calculated.
				if (read(fd[i][0], &rowCompleted, sizeof(int)) == -1) {
					fprintf(stderr, "Error while reading value. Problematic child: %d\n",
					        childPID);
					exit(1);
				}

				// Reads in the row values that the child process calculated.
				if (read(fd[i][0], rowResult, sizeof(int) * MAX_COLUMNS) == -1) {
					fprintf(stderr, "Error while reading value. Problematic child: %d\n",
					        childPID);
					exit(1);
				}

				close(fd[i][0]); // Close the read pipe after use.
				fillRow(rowCompleted, rowResult, tempResult);
			} else {
				// In case the child process failed.
				fprintf(stderr, "Child %d exited abnormally with code %d.\n", childPID,
				        exitStatus);
				exit(1);
			}
		}
	}
	return 0;
}

/**
 * Reads passed in A matrix from the parent, creates an array out of it, does
 * matrix multiplication with the passed in A matrix and the previously passed
 * in W matrix.
 *
 **/
int readAMatrix() {
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

		FILE *aMatrix = fopen(aMatrixFile, "r");
		if (aMatrix == NULL) {
			fprintf(stderr, "error: cannot open file %s read in from stdin\n",
			        aMatrixFile);
			fprintf(stderr, "Terminating, exit code 1.\n");
			return 1;
		}

		int tempA[MAX_ROWS][MAX_COLUMNS];
		memset(tempA, 0, sizeof(tempA));

		fillMatrix(&(tempA[0][0]), MAX_ROWS, MAX_COLUMNS, aMatrix);

		int tempAResult[MAX_ROWS][MAX_COLUMNS];
		memset(tempAResult, 0, sizeof(tempAResult));

		if ((doMatrixMult(&(tempA[0][0]), &(tempAResult[0][0]))) == 1) {
			fprintf(stderr, "Matrix Multiplication with stdin args failed.\n");
			return 1;
		}

		matrixSize += PRODUCT;
		int *tempResultArray = (int *)realloc(finalResultantMatrix, matrixSize * sizeof(int));
		if (tempResultArray == NULL) {
			fprintf(stderr, "realloc() failed for matrix %s.", aMatrixFile);
			matrixSize -= PRODUCT;
			return 1;
		}
		finalResultantMatrix = tempResultArray;

		appendToResultant(&(tempAResult[0][0]));
	}

	return 0;
}

/**
 * Appends the value of the first array to the end of the second.
 *
 * @attention The second array is large enough to fit in the first.
 *
 * @param tempResult The array whose values are to be appended.
 **/
void appendToResultant(int *tempResult) {
	int *resultStart = finalResultantMatrix + (matrixSize - PRODUCT);
	for (int i = 0; i < PRODUCT; ++i) {
		*(resultStart + i) = *(tempResult + i);
	}
}

/**
 * Calculates the dot product of the specified row in matrix1 with the entirety
 * of matrix2, and stores the result in the product result.
 *
 * @attention matrix1 and matrix 2 have a size of 8x8, and the product matrix
 * has a size of 1x8.
 *
 * @param matrix1 Matrix with the size 8x8.
 * @param matrix2 Matrix with the size 8x8.
 * @param product Matrix in which the dot product will be stored. Must be of size 1x8.
 *
 **/
void rowSum(const int *matrix1, const int *matrix2, int *product, const int row) {
	// Calculates the row to be multiplied.
	const int rowStart = row * MAX_ROWS;

	// Loop calculates the dot product of matrix1 and matrix2, and stores the
	// result in product.
	for (int i = 0; i < MAX_COLUMNS; ++i) {
		// Stores the result of multiplication of the entire row and column.
		int result = 0;

		// Loop calculates single row and single column multiplication.
		for (int j = 0; j < MAX_ROWS; ++j) {

			/**
			 * Multiplies one row and one column and stores the output in result.
			 * For the first value, we add the row increment with rowStart to both,
			 *get to the appropriate row for multiplication and to the corresponding
			 *row position. By dereferencing that address, we get the raw value.
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
		 * (offset calculated with the pointer address plus column increment, i) in
		 *the product array.
		 **/
		*(product + i) = result;
	}
}

/**
 * Fills the specified row in the resultant matrix with the values from the
 * source matrix.
 *
 * @attention The row parameter must be an index between 0 to 7.
 *
 * @param row The row index in the resultant matrix to be filled.
 * @param sourceMatrix The matrix containing the values to be copied from.
 * @param resultant: The resultant matrix to be filled.
 *
 **/
void fillRow(const int row, const int *sourceMatrix, int *resultant) {
	const int rowStart = row * MAX_ROWS;
	for (int i = 0; i < MAX_COLUMNS; ++i) {
		*(resultant + (rowStart + i)) = *(sourceMatrix + i);
	}
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
int closeAll(FILE *A, FILE *W, int *toFreeArray) {
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
void printArr(const int *resultant, const int size) {
	for (int i = 0; i < size; ++i) {
		if ((i != 0) && (i % MAX_COLUMNS == 0)) {
			fprintf(stdout, "\n");
		}
		fprintf(stdout, "%d ", *(resultant + i));
	}
	fprintf(stdout, "]\n");
}
