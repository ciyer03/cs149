/**
 * Description: Gathers as input from the user a dividend and a divisor, 
 * then divides the dividend three times consecutively by the divisor.
 * Author names: Chandramouli Iyer 
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: September 11th
 * Creation date: September 11th
 **/

#include <stdio.h>

int main(void) {
    int userNum = 0;
    int divNum = 0;

    printf("Enter a dividend and a divisor separated by spaces: ");
    scanf("%d %d", &userNum, &divNum);

    if (divNum == 0) {
        printf("The divisor cannot be zero.");
        return 1;
    }
    printf("The divident divided three times consecutively: \n%d, %d, %d\n", 
           (userNum / divNum), ((userNum / divNum) / divNum), 
           (((userNum / divNum) / divNum) / divNum));
    return 0;
}
