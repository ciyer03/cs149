/*
 * Description: Program that prints the PID of the current process 4 times.
 * Author names: Chandramouli Iyer
 * Author emails: chandramouli.iyer@sjsu.edu
 * Last modified date: 10/2/2023
 * Creation date: 10/1/2023
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PROCESSES 3

int main(void) {

    char msg[] = "hello world from PID";
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("%s %d\n", msg, getpid());
            exit(0);
        }
    }

    for (int i = 0; i < MAX_PROCESSES; ++i) {
        wait(NULL);
    } 
    
    printf("%s %d\n", msg, getpid());

    return 0;
}
