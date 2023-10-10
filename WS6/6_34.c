/*
 * Description: 6.34 LAB: Multiples of ten in an array
 * Author names: Chandramouli Iyer
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: 10/9/2023
 * Creation date: 10/9/2023
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool IsArrayMult10(int inputVals[], int numVals);
bool IsArrayNoMult10(int inputVals[], int numVals);

int main(void) {
    char userNums[500]; // Assuming the overall numbers won't exceed 500 chars.
    int nums[20];
    int readInNums = 0;
    printf("Enter upto 20 numbers: ");
    if (fgets(userNums, sizeof(userNums), stdin) == NULL) {
        printf("IO Error.\n");
        return 1;
    }

    if (userNums[strlen(userNums) - 1] == '\n') {
        userNums[strlen(userNums) - 1] = '\0'; // Get rid of newline character.
    }

    char *fetch = strtok(userNums, " "); // Read in a number separated by spaces.

    // Read in only 20 numbers and that we haven't reached EOL.
    for (int i = 0; i < 20 && fetch != NULL; ++i) {
        int number = atoi(fetch);
        nums[i] = number;
        readInNums++;
        fetch = strtok(NULL, " ");
    }

    // If both methods return false, it means that the array has mixed values.
    if (!(IsArrayMult10(nums, readInNums)) && !(IsArrayNoMult10(nums, readInNums))) {
        printf("mixed values\n");
    } else if (IsArrayNoMult10(nums, readInNums)) { // Check if array has no multiples of 10
        printf("no multiples of 10\n");
    } else if (IsArrayMult10(nums, readInNums)) { // Check if array only has multiples of 10
        printf("all multiples of 10\n");
    }

    return 0;
}

/*
 * Indicates if the array only contains multiples of 10. Uses the modulus operator to 
 * determine if there is an undesired value, since val % 10 returns 0 if val is a multiple 
 * of 10, and the remainder otherwise.
 *
 * Input Parameters: inputVals[] -> The array containing the vals.
 *                   numVals -> The amount of values in the array.
 *
 * Returns: a bool value indicating if the array only contains multiples of 10.
 */
bool IsArrayMult10(int inputVals[], int numVals) {
    bool isMult = true;
    for (int i = 0; i < numVals; ++i) {
        if (inputVals[i] % 10 != 0) {
            isMult = false;
            break; // No need to iterate more after one undesired value.
        }
    }
    return isMult;
}

/*
 * Indicates if the array doesn't contain any multiples of 10. Uses the modulus operator 
 * to determine if there is an undesired value, since val % 10 returns 0 if val is a 
 * multiple of 10, and the remainder otherwise.
 *
 * Input Parameters: inputVals[] -> The array containing the vals.
 *                   numVals -> The amount of values in the array.
 *
 * Returns: a bool value indicating if the array doesn't contain any multiples of 10.
 */
bool IsArrayNoMult10(int inputVals[], int numVals) {
    bool isNotMult = true;
    for (int i = 0; i < numVals; ++i) {
        if (inputVals[i] % 10 == 0) {
            isNotMult = false;
            break; // No need to iterate more after one undesired value.
        }
    }
    return isNotMult;
}
