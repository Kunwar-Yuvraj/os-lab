// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/fib_shm"
#define MAX 100

int main() {
    int fd, *shm_ptr, num;
    pid_t pid;

    // Create shared memory object
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, MAX * sizeof(int));

    // Fork and execute child
    if ((pid = fork()) == 0) {
        execl("./child", "child", NULL);
        perror("execl");
        exit(1);
    }
    wait(NULL);

    // Attach and read from shared memory
    shm_ptr = mmap(NULL, MAX * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    num = shm_ptr[0];
    printf("Fibonacci series:\n");
    for (int i = 1; i <= num; i++) printf("%d ", shm_ptr[i]);
    printf("\n");

    // Cleanup
    munmap(shm_ptr, MAX * sizeof(int));
    shm_unlink(SHM_NAME);
    close(fd);
    return 0;
}
