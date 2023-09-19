/**
* Description: Program to find the maximum number in a set of numbers, and the average of the numbers provided by the user.
* Name: Safiullah Saif
* Date Created: 09/16/2023
* Last Date Modified: 09/18/2023
*
*/

#include <stdio.h>

//This is the main function. Provides the required code for the program to run.
int main(int argc, char *argv[])
{
    int num;
    printf("Enter the non-negative numbers: ");
    scanf("%d", &num);
    double total = 0;
    int max = num;
    int count = 0;
    while (num >= 0) {
        total += num;
        count ++;
        scanf("%d", &num);

        if (num > max) {
            max = num;
        }
    }
    double avg = total/count;
    printf("%d %.2lf\n", max, avg);
    return 0;
}
