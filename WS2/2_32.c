/**
* Description: Inputs two numbers from the user and gives the user, the price of house, the change in price since last month, and the estimated monthly mortgage of the house.
* Name: Safiullah Saif
* Author email: safiullah.saif@sjsu.edu
* Creation Date: 09/08/2023
* Last Modified Date: 09/11/2023
* */

# include <stdio.h>

// The main function to take the inputs and generate the desired output.
int main(int argc, char *argv[])
{
    int firstAmt;
    int secondAmt;
    printf("Enter the two numbers: \n");
    scanf("%d %d", &firstAmt, &secondAmt);
    double change = firstAmt - secondAmt;
    double mort = (firstAmt * 0.051) / 12;
    printf("This house is $%d. The change is $%.0lf since last month.\nThe estimated monthly mortgage is $%lf.\n", firstAmt, change, mort);
    return 0;
}
