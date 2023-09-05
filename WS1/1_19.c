/**
* file: 1_19.c
* author: Chandramouli Iyer
* date: September 1st, 2023
* purpose: Prints out the square and cube of the first input, and then the sum and product of the first and second inputs.
*/

#include <stdio.h>

int main(void) {
    int userNum = 0;
    printf("Enter integer:\n");

    // Input Validation checking if the given input is actually a number or not.
    if (scanf("%d", &userNum) == 1) {
       printf("You entered: %d\n", userNum);
    } else {
        printf("Enter a valid integer.\n");
        return 1;
    }

    printf("%d squared is %d\n", userNum, (userNum * userNum)); // No need to separately declare a variable.
    printf("And %d cubed is %d\n", userNum, (userNum * userNum * userNum)); // No need to separately declare a variable.

    int userNum2 = 0;
    printf("Enter another integer:\n");

    // Input Validation
    if (scanf("%d", &userNum2) == 1) {
       printf("You entered: %d\n", userNum2);
    } else {
        printf("Enter a valid integer.\n");
        return 1;
    }
    
    printf("%d + %d is %d\n", userNum, userNum2, (userNum + userNum2));
    printf("%d * %d is %d\n", userNum, userNum2, (userNum * userNum2));
    
    return 0;
}
