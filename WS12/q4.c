/**
 * Description:
 * Author names: Chandramouli Iyer and Safiullah Saif
 * Author emails: chandramouli.iyer@sjsu.edu and safiullah.saif@sjsu.edu
 * Last modified date: 11/27/2023
 * Creation date: 11/27/2023
 *
 * What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind(again with the --leak-check=yes flag)?
 *
 * When this program runs, a certain memory is allocated in the heap (4, in this case as we are using an integer),
 * but does not free this allocated memory from the heap. Yes, you can use both, gdb and valgrind to solve such kind of problems,
 * as these resources are very efficient and helpful to solve problems related to memory allocation and management.
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = (int *)malloc(sizeof(int));

    return 0;
}
