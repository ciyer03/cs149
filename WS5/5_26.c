/*
 * Description: 5.26 LAB: Count input length without spaces, periods, exclamation points, or commas
 * Author names: Chandramouli Iyer
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: 10/1/2023
 * Creation date: 10/1/2023
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char input[50];
    printf("Enter a sentence (less than 50 characters): ");

    // Validate if fgets() exited successfully.
    if ((fgets(input, sizeof(input), stdin)) == NULL) {
        printf("\nIO Error.");
        return 1;
    }

    int count = 0;
    
    // Iterate through all characters.
    for (int i = 0; i < sizeof(input); ++i) {
        if (input[i] == '\n') { // Signifies end of the sentence.
            break;
        } 
        
        // Check for characters not to be counted.
        else if ((input[i] != ' ') && (input[i] != '.') && (input[i] != '!') && (input[i] != ',')) {
            count++;
        }
    }

    printf("\n%d\n", count); // Print the character count.
    return 0;
}
