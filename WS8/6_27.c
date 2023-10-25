/**
 * Description: Count the number of characters
 * Author names: Safiullah Saif, Chandramouli Iyer
 * Author emails: safiullah.saif@sjsu.edu, chandramouli.iyer@sjsu.edu
 * Last modified date: 10/23/2023
 * Creation date: 10/21/2023
 **/

#include <stdio.h>
#include <string.h>

int CalcNumCharacters(char* userString, char userChar);

/**
 * This is the main function. This takes the input character and string from the user, and passes it to the
 * CalcNumCharacters() function for its further processing.
**/
int main(void) {

    char userChar;
    char userString[50];
    printf("Enter a character followed by a string: ");
    if (scanf("%c %s", &userChar, userString) == EOF) {
        printf("I/O Error.\n");
        return 1;
    }

    int count = CalcNumCharacters(userString, userChar);

    if (count == 1) {
        printf("%d %c\n", count, userChar);
    }

    else {
        printf("%d %c's\n", count, userChar);
    }

    return 0;
}

/**
 * This function calculates the count of the number of times the character userChar 
 * appears in the string userString
 * 
 * Assumption: the user gives 2 inputs, first is a character of length 1, and second is a 
 * string
 * 
 * Input parameters: userString = the string given by the user
 *                   userChar = the character to find in userString
 * 
 * Returns: the number of appearances of userChar in userString.
 **/
int CalcNumCharacters(char* userString, char userChar) {
    int numChars = strlen(userString);
    int appearances = 0;
    for (int i = 0; i < numChars; ++i) {  
        if (userChar == *(userString + i)) {
            appearances++;
        }
    }
    return appearances;
}
