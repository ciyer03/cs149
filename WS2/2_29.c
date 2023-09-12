/**
 * Description: Gathers three float values, x, y, z from the user, and 
 * then calculates (x ^z), (x ^ (y ^ 2)), the absolute value of y, and 
 * the square root of (xy to the power of z).
 * Author names: Chandramouli Iyer 
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: September 11th
 * Creation date: September 11th
 **/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {

    float x, y, z;
    printf("Enter three float values separated by spaces: ");
    scanf("%f %f %f", &x, &y, &z);

    // pow() calculates the first argument raised to the second argument.
    // fabs() calculates the absolute value of a float input.
    // sqrtf() calculates the square root of a float input.
    printf("%.2lf %.2lf %.2lf %.2lf\n", pow(x, z), pow(x, pow(y, 2)), 
           fabs(y), sqrtf((powf((x * y), z))));
    return 0;
}
