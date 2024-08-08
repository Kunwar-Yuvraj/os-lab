// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SHM_NAME "/prime_shm"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s M N\n", argv[0]);
        return 1;
    }

    int m = atoi(argv[1]), n = atoi(argv[2]);
    int *shm, fd;

    if (fork() == 0) {
        execl("./child", "child", argv[1], argv[2], NULL);
        perror("execl");
        exit(1);
    }
    wait(NULL);

    fd = shm_open(SHM_NAME, O_RDWR, 0666);
    shm = mmap(NULL, sizeof(int) * 1001, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    printf("Primes between %d and %d:\n", m, n);
    for (int i = 1; i <= shm[0]; i++) printf("%d ", shm[i]);
    printf("\n");

    munmap(shm, sizeof(int) * 1001);
    shm_unlink(SHM_NAME);
    return 0;
}
