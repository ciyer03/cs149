/**
 * Description: This program multiplies the supplied W matrices, and A matrix. From that, it creates a RSum 
 * matrix. The program then accepts from stdin. It then multiplies each supplied matrix with the previously 
 * created RSum matrix, 
 * stdout. It uses multiple child processes to achieve this a faster way.
 * Author names: Chandramouli Iyer, Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu, safiullah.saif@sjsu.edu
 * Last modified date: October 30th
 * Creation date: October 26th
 **/

#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <wait.h>

#define MAX_ROWS 8
#define MAX_COLUMNS 8
#define PRODUCT (MAX_ROWS * MAX_COLUMNS)
#define FN_SIZE 15 // Assuming filenames (PID.out and PID.err) won't each exceed 15 characters.

int rSumMatrix[MAX_ROWS][MAX_COLUMNS];
const char *rMatrixFilename = "rSumMatrix.txt";

void aggregateFiles();
void getRMatrix(const char *input, char** matrices, const int numMatrices);
void sumRMatrix(const int *toAdd);
void writeRMatrix(); 
void printRMatrix();

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
    if (argc < 3) {
        printf("error: expecting at least 2 files as input.\n");
        printf("Terminating, exit code 1.\n");
        return 1;
    }

    int numWMatrices = argc - 2;
    for (int i = 0; i < numWMatrices; ++i) {
        int wMatrixIndex = argc - (numWMatrices - i);
        char **wMatrices = (char *[]) {argv[wMatrixIndex]};
        getRMatrix(argv[1] ,wMatrices, 1);
    }

    aggregateFiles();
    return 0;
}

/**
 * 
 * 
 * Assumption:
 *
 * Input:
 **/
void aggregateFiles() {
    char *userLineBuffer = NULL;
    size_t userBufferLen = 0;

    while (getline(&userLineBuffer, &userBufferLen, stdin) != -1) {
        userLineBuffer[strlen(userLineBuffer - 1)] = '\n';
        char *userBufferDup = strdup(userLineBuffer);

        char *wMatrix = strtok(userLineBuffer, " ");
        int numFiles = 1;
        while (wMatrix != NULL) {
            numFiles++;
            wMatrix = strtok(NULL, " ");
        }

        char **wMatrices = (char**) malloc(numFiles * sizeof(char *));
        if (wMatrices == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        wMatrix = strtok(userBufferDup, " ");
        int i = 0;
        while (wMatrix != NULL) {
            wMatrices[i] = strdup(wMatrix);
            ++i;
            wMatrix = strtok(NULL, " ");
        }
        free(userBufferDup);

        getRMatrix(rMatrixFilename, wMatrices, numFiles);
    }

    if (userLineBuffer != NULL) { 
        free(userLineBuffer);
    }
}

/**
 * 
 * 
 * Assumption:
 *
 * Input: 
 **/
void getRMatrix(const char *inputMatrix, char **wMatrices, const int numMatrices) {
    char outFile[FN_SIZE];
    char errFile[FN_SIZE];



    int childResult[MAX_ROWS][MAX_COLUMNS];

    if (wMatrices != NULL) {
        for (int i = 0; i < numMatrices; ++i) {
            free(wMatrices[i]);
        }
        free(wMatrices);
    }

    sumRMatrix(&(childResult[0][0]));
}

/**
 * Sums the given matrix and the rSumMatrix and stores the result in rSumMatrix.
 * 
 * Assumption: Both matrices are of size MAX_ROWS x MAX_COLUMNS
 *
 * Input: toAdd -> The matrix whose content will be summed.
 **/
void sumRMatrix(const int *toAdd) {
    int *rSum = &rSumMatrix[0][0];

    for (int i = 0; i < PRODUCT; ++i) {
        *(rSum + i) += *(toAdd + i);
    }

    writeRMatrix();
}

/**
 *
 *
 **/ 
void writeRMatrix() {
    int *matrix = &(rSumMatrix[0][0]);
    FILE *fd = fopen(rMatrixFilename, "w");

    for (int i = 0; i < PRODUCT; ++i) {
        if ((i % MAX_COLUMNS == 0) && i != 0) {
            fprintf(fd, "\n");
        }
        fprintf(fd, "%d ", *(matrix + i));
    }
}

/**
 * 
 * 
 * Assumption:
 *
 * Input: 
 **/
void printRMatrix() {

}
