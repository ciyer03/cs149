#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = atoi(argv[1]);

    int *sharedArray = mmap(NULL, sizeof(int) * 64, 
                            PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (sharedArray == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    for (int i = 0; i < 64; ++i) {
        sharedArray[i] = i;
    }

    printf("Done writing values in prog2.\n");

    return 0;
}
