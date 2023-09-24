/**
 * Description: Program to calculate the maximum and minimum value of number from the given input of 4 integers.
 * Name: Safiullah Saif
 * Date Created: 09/20/2023
 * Last Date Modified: 09/23/2023
 */

#include <stdio.h>
#include "MaxNumber.h"
#include "MinNumber.h"

//This is the main function. This function takes in 4 integers from the user, and calls the MaxNumber() and MinNumber() functions to calculate the maximum and minimum number from the given set of input integers respectively.
int main() {

    int num1, num2, num3, num4;
    printf("Enter the 4 numbers: ");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);
    MaxNumber(num1, num2, num3, num4);
    MinNumber(num1, num2, num3, num4);
    return 0;
}