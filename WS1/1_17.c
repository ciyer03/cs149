/**
 *file: 1_17.c
 *name: Safiullah Saif
 *date: 2023-09-04
 *purpose: Prints the arrow, including the BaseHead and the ArrowHead
*/

// Enables the input/output functionality
#include <stdio.h>

// This is the main function. This function prints out the desired output.
int main(int argc, char *argv[])
{
    int headInt;
    int baseInt;
    
    scanf("%d %d", &baseInt, &headInt);
    printf("    %d\n", headInt);
    printf("    %d%d\n", headInt, headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);    
    printf("%d%d%d%d%d%d%d%d\n", baseInt,baseInt,baseInt, baseInt, headInt, headInt, headInt, headInt);    
    printf("%d%d%d%d%d%d%d\n", baseInt,baseInt,baseInt,headInt, headInt, headInt, headInt);    
    printf("    %d%d\n", headInt, headInt);    
    printf("    %d\n", headInt);    
    return 0;
}
