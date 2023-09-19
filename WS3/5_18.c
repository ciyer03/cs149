/*
* Description: Program to return the middle of a list of given numbers from the user.
* Name: Safiullah Saif
* Date Created: 09/16/2023
* Last Date Modified: 09/18/2023
*/

#include <stdio.h>

//This is the main function. This is used to generate the desired output from the input given by the user.
int main(int argc, char *argv[])
{
    int count = 1;
    int num;
    int list[9];
    scanf("%d", &num);
    list[0] = num;
    while (count < 9 && num != -1) {
        scanf("%d", &num);
        list[count] = num;
        count++;
    }

    int midItem = list[count/2] - 1;

    if (count >= 9) {
        printf("Too many numbers");
    }
    else {
        printf("%d\n", midItem);
    }

    return 0;
}
