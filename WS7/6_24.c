/*
 * Description: 6.24 LAB: This program swaps 2 numbers, first with second input, and the third with fourth input
 * Author names: Safiullah Saif
 * Author emails: safiullah.saif@sjsu.edu
 * Last modified date: 10/11/2023
 * Creation date: 10/11/2023
 */

#include <stdio.h>


void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4);

/**
 * This is the main function that takes th input from the user, runs the SwapValues() function, and prints the reversed integers
 * Assumption: The user inputs 4 valid integers
 * Input parameters: nothing
 * Returns: 0 on success
**/
int main(void) {
    printf("Enter 4 numbers: ");
    int n1, n2, n3, n4;
    scanf("%d %d %d %d", &n1, &n2, &n3, &n4);
    //printf("%d %d %d %d", n1, n2, n3, n4);
    SwapValues(&n1, &n2, &n3, &n4);
    printf("%d %d %d %d\n", n1, n2, n3, n4);

    return 0;
}

/**
 * This function performs the required swap between the 4 inputs given
 * Assumption: There are 4 valid integers as the parameters being given while function call
 * Input parameters: userVal1, userVal2, userVal3, and userVal4
 * Returns: nothing
**/
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4) {

}

