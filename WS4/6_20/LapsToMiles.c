#include <stdio.h>

//This function calculates the number of miles depending on the number of miles, which is given as a parameter while calling this funciton, and prints the number of miles as the output accordingly.
int LapsToMiles(double laps) {

    double miles = laps / 4;
    printf("%0.2lf\n", miles);
}