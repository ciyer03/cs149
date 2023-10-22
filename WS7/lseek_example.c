// C program to read nth byte of a file and
// copy it to another file using lseek
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void func(char arr[], int n)
{
    // Open the file for READ only.
    int f_read = open("start.txt", O_RDONLY);

    // Open the file for WRITE and READ only.
    int f_write = open("end.txt", O_WRONLY | O_CREAT, 0777);

    while (read(f_read, arr, 1))
    {
        // Because every time we skip two characters from the current position.
        off_t offset = 2; 
        lseek(f_read, offset, SEEK_CUR);
        write(f_write, arr, 1);
    }
    close(f_write);
    close(f_read);
}

// Driver code
int main()
{
    char arr[100];
    int n;
    n = 5;

    // Calling for the function
    func(arr, n);
    return 0;
}
