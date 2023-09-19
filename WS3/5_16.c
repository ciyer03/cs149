/**
 * Description: This program prints the entered in numbers in reverse.
 * Author Name: Chandramouli Iyer
 * Author Email: chandramouli.iyer@sjsu.edu
 * Last Modified Date: September 18th
 * Creation Date: September 18th
**/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int numInputs = 0;
    printf("Enter the number of inputs you will give: ");

    // Checks if the scanf function was successful, and if not, exit.
    if ((scanf("%d", &numInputs) < 0)) {
        printf("\nIO Error.\n");
        return 1;
    }

    // Number of inputs cannot be less than 0.
    while (numInputs <= 0) {
        printf("\nThe number of inputs must be greater than 0.\n");
        printf("Enter the number of inputs you will give: ");

        // Checks if the scanf function was successful, and if not, exit.
        if ((scanf("%d", &numInputs)) < 0) {
            printf("\nIO Error.\n");
            return 1;
        }
    }

    int inputs[numInputs];

    // Get the integer inputs from the user.
    for (int i = 0; i < numInputs; ++i) {
        printf("\nEnter a number: ");

        // Checks if the scanf function was successful, and if not, exit.
        if ((scanf("%d", &(inputs[i])) < 0)) {
            printf("\nIO Error.\n");
            return 0;
        }
    }

    printf("Numbers in reverse order: ");
    
    // Prints the number in reverse order.
    for (int i = numInputs - 1; i >= 0; --i) {
        printf("%d, ", inputs[i]);   
    }

    printf("\n");

    return 0;
}
