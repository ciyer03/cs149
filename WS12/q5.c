/**
 * Description:
 * Author names: Chandramouli Iyer and Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu and safiullah.saif@sjsu.edu
 * Last modified date: 11/27/2023
 * Creation date: 11/27/2023
 *
 * What happens when you run this program? What happens when you runt his program using valgrind? Is the program correct?
 *
 * Program Execution:
 *
 * This program uses malloc to allocate memory for an array of 100 integers.
 * Then, the code makes an attempt to set the value of data[100], i.e. 100th index of the data array to zero,
 * which it fails to do so, since, the valid indices for the array are from 0 to 99.
 *
 * Use of Valgrind:
 *
 * When you run this program using Valgrind, the program will detect an error due to out-of-bounds memory.
 * It will further inform that this program is accessing the memory section beyond the allocated memory.
 *
 * Method to Correct the Program:
 *
 * To correct this method, you should access indices of data from 0 upto 99, as the same is the range of the data array provided in the code.
 * Additionally, use the free(data); statement at the end of the code to free the allocated memory to the data variable to prevent
 * any possible memory leaks.
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *data = malloc(100 * sizeof(int));

    if (data == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1; // Exiting the program with an error code
    }

    data[100] = 0;

    return 0;
}
