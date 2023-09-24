//This is the function to calculate the minimum number out of the 4 given parameters, which are the inputs given by the user in the form of integers.

#include <stdio.h>

int MinNumber(int num1, int num2, int num3, int num4) {
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
