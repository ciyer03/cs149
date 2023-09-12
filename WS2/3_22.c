/*
* Description: Inputs three integers from the user, and then prints out the integer with the minimum value.
* Name: Safiullah Saif
* Date Created: 09/08/2023
* Date last modified: 09/11/2023
*/

#include <stdio.h>


//This is the main function. This function compares the values of three integers, and then prints out the minimum value integer.

int main(int argc, char *argv[])
{
    int firstInt;
    int secondInt;
    int thirdInt;
      scanf("%d %d %d", &firstInt, &secondInt, &thirdInt);
    int min = firstInt;

    if (secondInt < thirdInt) {
        if (secondInt < min) {
            min = secondInt; 
        }
    }

    else {
        if (thirdInt < min) {
            min = thirdInt;
        }
    }
    printf("%d", min);

    return 0;
}
