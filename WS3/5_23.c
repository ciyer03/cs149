/**
 * Description: This program takes a list of integers, takes a lower and upper bound 
 * range, and prints out all integers from the list that fall within the range, inclusive
 * of the range numbers.
 * Author Name: Chandramouli Iyer
 * Author Email: chandramouli.iyer@sjsu.edu
 * Last Modified Date: September 18th
 * Creation Date: September 18th
**/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int numInputs = 0;
    printf("Enter the number of inputs you will supply: ");

    // Checks if the scanf function was successful, and if not, exit.
    if (scanf("%d", &numInputs) < 0) {
        printf("IO Error.\n");
        return 1;
    }

    // Number of inputs cannot be more than 20 and cannot be less than 0.
    while (numInputs > 19 || numInputs <= 0) {
        printf("\nEnter a number less than 20 and greater than 0: ");

        // Checks if the scanf function was successful, and if not, exit.
        if (scanf("%d", &numInputs) < 0) {
            printf("IO Error.\n");
            return 1;
        }
    }


    int inputs[numInputs];

    int upperRange = 0;
    printf("\nEnter upper range: ");

    // Checks if the scanf function was successful, and if not, exit.
    if (scanf("%d", &upperRange) < 0) {
        printf("IO Error.\n");
        return 1;
    }


    int lowerRange = 0;
    printf("\nEnter lower range: ");

    // Checks if the scanf function was successful, and if not, exit.
    if (scanf("%d", &lowerRange) < 0) {
        printf("IO Error.\n");
        return 1;
    }

    // Lower range must be lower than the upper range.
    while (lowerRange >= upperRange) {
        printf("\nThe upper range must be strictly greater than the lower range.\n");

        printf("Enter upper range: ");

        // Checks if the scanf function was successful, and if not, exit.
        if (scanf("%d", &upperRange) < 0) {
            printf("IO Error.\n");
            return 1;
        }

        printf("\nEnter lower range: ");

        // Checks if the scanf function was successful, and if not, exit.
        if (scanf("%d", &lowerRange) < 0) {
            printf("IO Error.\n");
            return 1;
        }
    }


    // Get the list of integers.
    for (int i = 0; i < numInputs; ++i) {
        printf("\nEnter a number: ");

        // Checks if the scanf function was successful, and if not, exit.
        if (scanf("%d", &(inputs[i])) < 0) {
            printf("IO Error.\n");
            return 1;
        }
    }

    printf("Elements in the range %d to %d: ", lowerRange, upperRange);

    // Prints the integers in the list that fall within the specified range.
    for (int i = 0; i < numInputs; ++i) {
        if ((inputs[i] >= lowerRange) && (inputs[i] <= upperRange)) {
            printf("%d, ", inputs[i]);
        }
    }

    printf("\n");
    return 0;
}
