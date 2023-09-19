/**
 * Description: This program takes in a list of integers, and then prints out all 
 * numbers from the list that are lower than a specified threshold.
 * Author Name: Chandramouli Iyer
 * Author Email: chandramouli.iyer@sjsu.edu
 * Last Modified Date: September 18th
 * Creation Date: September 18th
**/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int numInputs = 0;

    printf("Enter the number of values you will give: ");

    // Checks if the scanf function was successful, and if not, exit.
    if ((scanf("%d", &numInputs)) < 0) {
        printf("\nIO Error.\n");
        return 1;
    }

    // Number of inputs cannot be zero or less than it.
    while (numInputs <= 0) {
        printf("\nNumber of inputs must be greater than 0.\n");
        printf("Enter the number of values you will give: ");

        // Checks if the scanf function was successful, and if not, exit.
        if ((scanf("%d", &numInputs)) < 0) {
            printf("\nIO Error.\n");
            return 1;        
        }
    }

    int inputs[numInputs];

    // Gets the list of integers from the user.
    for (int i = 0; i < numInputs; ++i) {
        printf("\nEnter a number: ");

        // Checks if the scanf function was successful, and if not, exit.
        if ((scanf("%d", &(inputs[i]))) < 0) {
            printf("\nIO Error.\n");
            return 1;
        }
    }

    int threshold = 0;
    printf("\nEnter a threshold value: ");

    // Checks if the scanf function was successful, and if not, exit.
    if ((scanf("%d", &threshold)) < 0) {
        printf("\nIO Error.\n");
        return 1;
    }

    // Checks and prints each number in the list that is less than the threshhold.
    for (int i = 0; i < numInputs; ++i) {
        if (inputs[i] <= threshold) {
            printf("%d, ", inputs[i]);
        }
    }
    printf("\n");

    return 0;
}
