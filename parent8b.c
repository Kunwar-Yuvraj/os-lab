#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int n = 5;
    if (fork() == 0) {
        execl("./mera2", "mera2", NULL);
    }

    int fd = shm_open("/fibo_shm", O_RDWR, 0666);
    int *shm_addr = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    for (int i = 0; i < n; i++) {
        printf("%d ", shm_addr[i]);
    }

    munmap(shm_addr, n * sizeof(int));
    shm_unlink("/fibo_shm");
    return 0;
}
