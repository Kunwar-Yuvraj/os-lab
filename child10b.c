// child.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SHM_NAME "/prime_shm"
#define MAX_PRIMES 1000

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s M N\n", argv[0]);
        return 1;
    }

    int m = atoi(argv[1]), n = atoi(argv[2]);
    int *shm, fd, cnt = 0;

    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(int) * (MAX_PRIMES + 1));
    shm = mmap(NULL, sizeof(int) * (MAX_PRIMES + 1), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    for (int i = m; i <= n; i++) {
        if (i < 2) continue;
        int is_prime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) shm[++cnt] = i;
    }
    shm[0] = cnt;

    munmap(shm, sizeof(int) * (MAX_PRIMES + 1));
    return 0;
}
