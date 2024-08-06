#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUF_SIZE 2

void read_10_chars(int fd);
void skip_5_chars(int fd);
void go_5th_last(int fd);
void go_3rd(int fd);

int main() {
    int fd = open("5a.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    read_10_chars(fd);
    skip_5_chars(fd);
    go_5th_last(fd);
    go_3rd(fd);

    close(fd);
    return 0;
}

void read_10_chars(int fd) {
    char buf[11]; // 10 chars + null terminator
    ssize_t n = read(fd, buf, 10);
    if (n > 0) {
        buf[n] = '\0';
        printf("%s\n", buf);
    }
}

void skip_5_chars(int fd) {
    lseek(fd, 5, SEEK_CUR);
    read_10_chars(fd);
    
}

void go_5th_last(int fd) {
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, size - 5, SEEK_SET);
    char buf[BUF_SIZE];
    ssize_t n = read(fd, buf, 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("%s\n", buf);
    }
}

void go_3rd(int fd) {
    lseek(fd, 2, SEEK_SET);
    char buf[BUF_SIZE];
    ssize_t n = read(fd, buf, 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("%s\n", buf);
    }
}
