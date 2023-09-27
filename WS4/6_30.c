/**
 * Description: Program to calculate the maximum and minimum value of number from the given input of 4 integers.
 * Name: Safiullah Saif
 * Date Created: 09/20/2023
 * Last Date Modified: 09/23/2023
 */

#include <stdio.h>

int MaxNumber(int arr[4]);
int MinNumber(int arr[4]);

//This is the main function. This function takes in 4 integers from the user, and calls the MaxNumber() and MinNumber() functions to calculate the maximum and minimum number from the given set of input integers respectively.
int main() {

    int arr[4];
    printf("Enter the 4 numbers: ");

    for (int i = 0; i < 4; i++) {
        scanf("%d", &arr[i]);
    }

    int maxNum = MaxNumber(arr);
    int minNum = MinNumber(arr);

    printf("Maximum is %d\n", maxNum);
    printf("Minimum is %d\n", minNum);
    return 0;
}


//This is the function to calculate the maximum number out of the 4 given parameters, which are the inputs given by the user in the form of integers.
int MaxNumber(int arr[4]) {
    int max = arr[0];

    if (arr[1] > max) {
        max = arr[1];
    }
    if (arr[2] > max) {
        max = arr[2];
    }
    if (arr[3] > max) {
        max = arr[3];
    }
    return max;

}

//This is the function to calculate the minimum number out of the 4 given parameters, which are the inputs given by the user in the form of integers.
int MinNumber(int arr[4]) {
    int min = arr[0];

    if (arr[1] < min) {
        min = arr[1];
    }
    if (arr[2] < min) {
        min = arr[2];
    }
    if (arr[3] < min) {
        min = arr[3];
    }
    return min;

}