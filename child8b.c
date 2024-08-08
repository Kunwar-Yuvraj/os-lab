// child.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/fib_shm"
#define MAX 100

int main() {
    int fd, *shm_ptr, num;
    printf("Enter number of Fibonacci numbers: ");
    scanf("%d", &num);

    // Create shared memory object
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, MAX * sizeof(int));
    shm_ptr = mmap(NULL, MAX * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Generate Fibonacci series
    if (num > 0) shm_ptr[1] = 0;
    if (num > 1) shm_ptr[2] = 1;
    for (int i = 2; i < num; i++) shm_ptr[i + 1] = shm_ptr[i] + shm_ptr[i - 1];
    shm_ptr[0] = num;  // Number of elements

    // Cleanup
    munmap(shm_ptr, MAX * sizeof(int));
    close(fd);
    return 0;
}
