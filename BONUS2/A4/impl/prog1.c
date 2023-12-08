#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int resultmatrix[8][8];

int main(int argc, char *argv[]) {
    int fd = open("/tmp/mmap.tmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (ftruncate(fd, sizeof(int) * 64) == -1) {
        perror("ftruncate");
        return 1;
    }

    int *sharedResult = mmap(NULL, sizeof(int) * 64, 
                             PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (sharedResult == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        char fd_str[10];
        snprintf(fd_str, sizeof(fd_str), "%d", fd);
        char *args[] = { "prog2", fd_str, NULL };

        execv("./prog2.o", args);
        printf("execv failed()\n");
        return 1;
    }

    wait(NULL);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            resultmatrix[i][j] = *(sharedResult + i*8 + j);
            printf("%d ", resultmatrix[i][j]);
        }
    }
    printf("\n");
    munmap(sharedResult, sizeof(int) * 64);
    close(fd);
    unlink("/tmp/mmap.tmp");
    
    return 0;
}
