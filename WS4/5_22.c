/*
 * Description: 5.22 LAB: Contains the character
 * Author names: Chandramouli Iyer
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: September 26th, 2023
 * Creation date: September 24th, 2023
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void) {
    int numWords = 0;
    printf("Enter the number of words in the list: ");

    // Verify if scanf ran sucessfully.
    if ((scanf("%d", &numWords)) != 1) {
        printf("\nInvalid input or IO Error.\n");
        return 1;
    }

    char delim;
    // Clear out any newlines characters left by scanf.
    while ((delim = getchar() != '\n') && delim != EOF);

    char list[500];
    printf("\nEnter a sentence (less than 500 characters): ");

    // Read a sentence from stdin.
    if ((fgets(list, sizeof(list), stdin)) == NULL) {
        printf("\nError while reading line.\n");
        return 1;
    }

    // Remove the newline inserted by fgets.
    list[strlen(list) - 1] = '\0';

    printf("\nEnter the delimiter character: ");
    // Verify if scanf ran successfully.
    if ((scanf(" %c", &delim)) != 1) {
        printf("\nInvalid input or IO Error.\n");
        return 1;
    }

    // Get a word from the list.
    char *word = strtok(list, " ");

    // This loop analyzes the tokenized word for the delim character specified by user.
    // And only iterate through the number of words specified.
    while (word != NULL && numWords != 0) {
        bool hasDelim = false; // Keeps track of if the delim character is present.

        // Iterate through every letter of the word.
        for (int i = 0; (char) *(word + i) != '\0'; ++i) {

            // Check if the letter matches the delim character, and set hasDelim to true
            // if found.
            if ((char) (*(word + i)) == (char) delim) {
                hasDelim = true;
            }

            // No need to iterate more if the delim character has been found.
            if (hasDelim) {
               break;
            }
        }

        // Print out the word if the word has the delim character.
        if (hasDelim) {
            for (int i = 0; (char) *(word + i) != '\0'; ++i) {
                printf("%c", (char) (*(word + i)));
            }
            printf(",");
        }

        // Get the next word and decrement the number of words left to read.
        word = strtok(NULL, " ");
        numWords--;
    }

    printf("\n");
    return 0;
}
