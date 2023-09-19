/**
 * Description: This program converts a given integer to its respective binary form, and 
 * prints it out.
 * Author Name: Chandramouli Iyer
 * Author Email: chandramouli.iyer@sjsu.edu
 * Last Modified Date: September 18th
 * Creation Date: September 18th
**/

#include <stdio.h>
#define BINARY 2

int main(int argc, char *argv[]) {
    int input = 0;
    printf("Enter an integer: ");

    // Checks if the scanf function was successful, and if not, exit.
    if ((scanf("%d", &input)) < 0) {
        printf("\nIO Error.\n");
        return 1;
    }

    if (input == 0) { // Special case
        printf("0\n");
        return 0;
    } else if (input < 0) { // Invalid input.
        printf("Input cannot be negative.\n");
        return 1;
    }

    printf("\n");

    // Calculate the reverse binary form.
    while (input > 0) {
        int mod = input % BINARY;
        printf("%d", mod);
        input /= 2;
    }

    printf("\n");
    return 0;
}
