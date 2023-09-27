/**
 * Description: Program to calculate the number of miles covered depending of the number of laps given by the user.
 * Name: Safiullah Saif
 * Date Created: 09/20/2023
 * Last Date Modified: 09/23/2023
 */

#include <stdio.h>

double LapsToMiles(double laps);

// This is the main function. This function takes the number of laps as the input from the user, and calls the LapsToMiles() function.
int main() {

    double laps;
    printf("Enter the number of laps: ");
    scanf("%lf", &laps);
    double numMiles = LapsToMiles(laps);
    printf("%0.2lf\n", numMiles);
    return 0;
}

//This function calculates the number of miles depending on the number of miles, which is given as a parameter while calling this funciton, and prints the number of miles as the output accordingly.
double LapsToMiles(double laps) {

    double miles = laps / 4;
    return miles;

}