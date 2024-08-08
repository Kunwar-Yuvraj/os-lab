// child.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 1234
#define MAX 100

void gen_fib(int *p, int n);

int main() {
    int shmid;
    int *shm_ptr;
    int num;

    // Create shared memory
    shmid = shmget(SHM_KEY, MAX * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    shm_ptr = (int *) shmat(shmid, NULL, 0);
    if (shm_ptr == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Get number of Fibonacci numbers to generate
    printf("Enter number of Fibonacci numbers: ");
    scanf("%d", &num);
    
    // Store number of elements in the shared memory for parent to know
    shm_ptr[0] = num;

    // Generate Fibonacci series
    gen_fib(shm_ptr + 1, num);

    // Detach from shared memory
    if (shmdt(shm_ptr) < 0) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}

void gen_fib(int *p, int n) {
    int i;
    if (n <= 0) return;

    p[0] = 0;
    if (n == 1) return;

    p[1] = 1;
    for (i = 2; i < n; i++) {
        p[i] = p[i - 1] + p[i - 2];
    }
}
