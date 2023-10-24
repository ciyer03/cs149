/**
 * Description: Count the number of characters
 * Author names: Safiullah Saif, Chandramouli Iyer
 * Author emails: safiullah.saif@sjsu.edu, chandramouli.iyer@sjsu.edu
 * Last modified date: 10/22/2023
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
    scanf("%c %s", &userChar, userString);

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
 * This function calculates the count of the number of times the character userChar appears in the
 * string userString
 * Assumption: the user gives 2 inputs, first is a character of length 1, and second is a string
 * Input parameters: userString, userChar
 * Returns: an integer
 **/
int CalcNumCharacters(char* userString, char userChar) {


}
