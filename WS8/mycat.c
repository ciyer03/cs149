#include "apue.h"
#include <stdio.h>

#define	BUFFSIZE	4096

int main(void) {
    int		n;
    char	buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }

        if (n < 0) {
            err_sys("read error");
        }

        fprintf(stderr, "Bytes Read: %d\n", n);
    }
    exit(0);
}
