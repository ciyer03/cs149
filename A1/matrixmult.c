/**
 * Description: This program allows the user to multiply 3 matrices:
 * A, W, and B, or specific sizes. A, the input matrix, will be of 
 * size 1x3, W, the weights matrix, will be of size 3x5, and B, the 
 * bias matrix, will be of size 1x5. The resultant matrix, R, will 
 * be of size 1x5 as well.
 * Author names: Chandramouli Iyer 
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: September 8th
 * Creation date: September 8th
 **/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Supply exactly 3 files as arguments.\n");
        return 1;
    }


    return 0;
}
