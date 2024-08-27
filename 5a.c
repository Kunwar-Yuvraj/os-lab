#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BS 30

void main(){
    int buffer[BS];
    int fd = open("example.txt", O_RDWR);
    int n;

    printf("\nPrinting 10 characters from the file:\n");
    n = read(fd, buffer, 10);
    write(1, buffer, n);

    printf("\nSkipping 5 characters from current position:\n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);

    printf("\nGoing to 5th last character in the file:\n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buffer, 1);
    write(1, buffer, n);

    printf("\nGoing to 3rd character in the file:\n");
    lseek(fd, 3, SEEK_SET);
    n = read(fd, buffer, 1);
    write(1, buffer, n);
}
