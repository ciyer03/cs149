/**
* Description: Takes an input stringfrom the user, and then outputs the desired string.
* Name: Safiullah Saif
* Date Created: 09/08/2023
* Last Modified Date: 09/11/2023
*/


#include <stdio.h>

// This is the main function. This includes the code that we write for the desired output.
int main(int argc, char *argv[])
{
    char str[200];
    scanf("%s", str);
    printf("Hey %s!\nWelcome to zyBooks!\n", str);
    return 0;
}
