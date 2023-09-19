/*
* Description: Program to return the middle of a list of given numbers from the user.
* Name: Safiullah Saif
* Date Created: 09/16/2023
* Last Date Modified: 09/18/2023
*/

#include <stdio.h>
#define MAX_SIZE 9

//This is the main function. This is used to generate the desired output from the input given by the user.
int main(int argc, char *argv[])
{
    int count = 0; // Index count
    int input = 0; // Stores the user input

    int list[MAX_SIZE];

    // Reads in values from the input.
    while (input >= 0) {
        if (count > 9) { // Don't want to read in more than 9 values.
            printf("Too many numbers\n");
            return 1;
        }

        // Take input from the user.
        printf("\nEnter a number: ");
        if ((scanf("%d", &input)) < 0) {
            printf("\nIO Error.\n");
            return 1;
        }
        list[count] = input; // Store the value in the array.
        count++; // Increment the index.
    }

    // Gather the middle index.
    int midItem = list[(count/2) - 1];

    printf("Middle item: %d\n", midItem);

    return 0;
}
