/**
* file: 1_20.c
* author: Chandramouli Iyer
* date: September 1st, 2023
* purpose: Prints out two ASCII arts.
*/

#include <stdio.h>

int main(void) {
    int spaces = 3; // Number of spaces at the top.
    int asterisks = 1; //Number of asterisks at the top.
    
    // Prints out the first 4 lines of the ASCII art.
    for (int i = 0; i <= 3; ++i) {

        // Prints out the spaces.
        for (int j = spaces; j > 0; --j) {
            printf(" ");
        }
        --spaces; // Spaces decrease by one each line.
        
        // Prints out the asterisks.
        for (int k = 1; k <= asterisks; ++k) {
            printf("*");
        }
        printf("\n");
        asterisks += 2; // Asterisks increase by 2 each line.
    }

    printf("  ***\n\n\n"); // Last line of the first ASCII art.

    // Second ASCII art.
    printf("/\\   /\\\n");
    printf("  o o\n");
    printf(" =   =\n");
    printf("  ---\n");

    return 0;
}
