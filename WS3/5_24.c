/*
* Description: This program returns the minimum and the second minimum number from the given list of numbers from the user.
* Name: Safiullah Saif
* Date Created: 09/16/2023
* Last Date Modified: 09/18/2023
*/

#include <stdio.h>

//This is the main funciton. This function generates the desired output, which is printing the two minimum numbers from the given input, which is a list of numbers from the user.
int main(int argc, char *argv[])
{
    int count;
    scanf("%d", &count);
    int list[count];

    for (int i = 0; i < count; i++) {
        int num;
        scanf("%d", &num);
        list[i] = num; 
    }
    
    int firstMin;
    int secMin;

    if (list[0] < list[1]) {
        firstMin = list[0];
        secMin = list[1];
    }

    else {
        firstMin = list[1];
        secMin = list[0];
    }

    for (int i = 2; i < count; i++) {
        if (list[i] < secMin) {
            if (list[i] < firstMin) {
                secMin = firstMin;
                firstMin = list[i];
            }

            else {
                secMin = list[i];
            }
        }
    } 

    printf("%d and %d\n", firstMin, secMin);
    return 0;
}
