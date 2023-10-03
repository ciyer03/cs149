/*
 * Description: Program to print the string inputs that are given by the user in reverse
 * Author names: Safiullah Saif
 * Author emails: safiullah.saif@sjsu.edu
 * Date Created: 10/02/2023
 * Last Date Modified: 10/02/2023
 */

#include <stdio.h>
#include <string.h>

int main(void) {

    char input[51];
    printf("Enter a line of text (or 'Done', 'done', or 'd' to exit):\n");

    while (1){

        fgets(input, sizeof(input), stdin);

        // Removes any trailing newline character in the given input string
        size_t length = strlen(input);
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }

        // Checks if the user wants to exit the program or not
        if (strcmp(input, "Done") == 0 || strcmp(input, "done") == 0 || strcmp(input, "d") == 0) {
            break;
        }

        // Reverse the given input string
        for (int i = strlen(input) - 1; i >= 0; i--) {
            printf("%c", input[i]);
        }

        // Print a new line for the next input
        printf("\n");

    }

    return 0;
}