/**
 * Description:
 * Author names: Chandramouli Iyer and Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu and safiullah.saif@sjsu.edu
 * Last modified date: 11/27/2023
 * Creation date: 11/27/2023
 *
 * Does the program run? What happens when you use valgrind on it?
 *
 * Program Execution:
 *
 * This program uses malloc to allocate memory for an array of 100 integers.
 * Then, the code frees the memory allocated to the heap.
 * Then, the code makes an attempt to print the 0th index (first element) from the data array,
 * which it fails to do so, since, the memory is already freed from the heap.
 *
 * Use of Valgrind:
 *
 * When you run this program using Valgrind, the program will detect an error.
 * It will inform the user that the given code is trying to access a freed memory from the heap.
 *
 * Method to Correct the Program:
 *
 * To correct this method, you should access anything related the data array before freeing its allocated memory from the heap.
 *
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

    free(data);

    printf("Value of data[0]: %d\n", data[0]);

    return 0;
}
