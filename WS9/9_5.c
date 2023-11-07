/**
 * Description: This code returns the first and last name that the user inputs, or an error if the input is given without a comma
 * Author names:Safiullah Saif, Chandramouli Iyer
 * Author emails: safiullah.saif@sjsu.edu, chandramouli.iyer@sjsu.edu
 * Last modified date: 11/02/2023
 * Creation date: 11/03/2023
 **/

#include<stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

/**
 * This function returns the first and last name from the full name given as an input with a comma between the first and the last name
 * Assumption: The user inputs at least 2 strings with/without a comma in between the first and the last name (or q to quit the program)
 * Input parameters: first and last name with/without a comma (or q to quit the program)
 * Returns: nothing
**/
int main(void) {
    char input_string[100];

    while (1) {
        printf("Enter input string: ");
        scanf("%[^\n]%*c", input_string);

        if (strcmp(input_string, "q") == 0) {
            break;
        }

        if (strchr(input_string, ',') == NULL) {
            printf("Error: No comma in string.\n");
            continue;
        }

        char first_word[50], second_word[50];

        int i = 0, j = 0;
        while (input_string[i] != ',') {
            first_word[j++] = input_string[i++];
        }
        first_word[j] = '\0';

        i++; // This is to skip the comma
        j = 0;
        while (input_string[i] != '\0') {
            second_word[j++] = input_string[i++];
        }
        second_word[j] = '\0';

        // Remove any undesired leading or trailing spaces from the string
        for (i = 0; first_word[i] == ' '; i++);
        for (j = strlen(first_word) - 1; first_word[j] == ' '; j--);
        first_word[j + 1] = '\0';
        memmove(first_word, first_word + i, strlen(first_word + i) + 1);

        for (i = 0; second_word[i] == ' '; i++);
        for (j = strlen(second_word) - 1; second_word[j] == ' '; j--);
        second_word[j + 1] = '\0';
        memmove(second_word, second_word + i, strlen(second_word + i) + 1);

        printf("First word: %s\n", first_word);
        printf("Second word: %s\n", second_word);
    }

    return 0;
}


