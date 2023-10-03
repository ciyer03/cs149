/*
 * Description: Program to remove all existing non-alphabetic characters given in the input string from the user.
 * Name: Safiullah Saif
 * Date Created: 09/30/2023
 * Last Date Modified: 10/01/2023
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//This is the function that removes the non-alphabetical characters from the user's input.
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
    int i, j = 0;
    int length = strlen(userString);

    for (i = 0; i < length; i++) {
        // Checks if the character is an alphabet letter or not
        if (isalpha(userString[i])) {
            // If yes, then add the character to the result string
            userStringAlphaOnly[j] = userString[i];
            j++;
        }
    }
}

int main(void) {
    char userString[51]; // Assuming that the input string will not exceed 50 characters
    char userStringAlphaOnly[51];

    // Read input from the user
    printf("Enter a string (not exceeding 50 characters): ");
    fgets(userString, sizeof(userString), stdin);

    // Remove any possible non-alphabetic characters present in the input
    RemoveNonAlpha(userString, userStringAlphaOnly);

    // Print the modified input
    printf("Modified string: %s\n", userStringAlphaOnly);

    return 0;
}
