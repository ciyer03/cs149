//This is the function to calculate the maximum number out of the 4 given parameters, which are the inputs given by the user in the form of integers.

#include <stdio.h>

int MaxNumber(int num1, int num2, int num3, int num4) {
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