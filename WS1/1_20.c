/**
* file: 1_20.c
* author: Chandramouli Iyer
* date: September 1st, 2023
* purpose: Prints out two ASCII arts.
*/

#include <stdio.h>

int main(void) {
    int spaces = 3;
    int asterisks = 1;
    for (int i = 0; i <= 3; ++i) {
        for (int j = spaces; j > 0; --j) {
            printf(" ");
        }
        --spaces;
        
        for (int k = 1; k <= asterisks; ++k) {
            printf("*");
        }
        asterisks += 2;
        printf("\n");
    }
    printf("  ***\n\n\n");

    printf("/\\   /\\\n");
    printf("  o o\n");
    printf(" =   =\n");
    printf("  ---\n");

    return 0;
}
