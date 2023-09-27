/**
 * Description: Program to calculate the maximum and minimum value of number from the given input of 4 integers.
 * Name: Safiullah Saif
 * Date Created: 09/20/2023
 * Last Date Modified: 09/23/2023
 */

#include <stdio.h>

void MaxNumber(int num1, int num2, int num3, int num4);
void MinNumber(int num1, int num2, int num3, int num4);

//This is the main function. This function takes in 4 integers from the user, and calls the MaxNumber() and MinNumber() functions to calculate the maximum and minimum number from the given set of input integers respectively.
int main() {

    int num1, num2, num3, num4;
    printf("Enter the 4 numbers: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
    MaxNumber(num1, num2, num3, num4);
    MinNumber(num1, num2, num3, num4);
    return 0;
}


//This is the function to calculate the maximum number out of the 4 given parameters, which are the inputs given by the user in the form of integers.
void MaxNumber(int num1, int num2, int num3, int num4) {
    int max = num1;

    if (num2 > max) {
        max = num2;
    }
    if (num3 > max) {
        max = num3;
    }
    if (num4 > max) {
        max = num4;
    }
    printf("Maximum is %d\n", max);
}

//This is the function to calculate the minimum number out of the 4 given parameters, which are the inputs given by the user in the form of integers.
void MinNumber(int num1, int num2, int num3, int num4) {
    int min = num1;

    if (num2 < min) {
        min = num2;
    }
    if (num3 < min) {
        min = num3;
    }
    if (num4 < min) {
        min = num4;
    }
    printf("Minimum is %d\n", min);
}