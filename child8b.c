#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void gen_fibo(int *shm_addr, int n) {
    if (n <= 0) return;
    shm_addr[0] = 0;
    if (n > 1) shm_addr[1] = 1;

    for (int i = 2; i < n; i++) {
        shm_addr[i] = shm_addr[i - 1] + shm_addr[i - 2];
    }
}

int main() {
    int n = 10;
    int fd = shm_open("/fibo_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, n * sizeof(int));
    int *shm_addr = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    gen_fibo(shm_addr, n);
    munmap(shm_addr, n * sizeof(int));
    return 0;
}
