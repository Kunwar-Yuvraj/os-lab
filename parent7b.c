// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_KEY 1234
#define MAX 100

void print_fib(int *p, int n);

int main() {
    int shmid;
    int *shm_ptr;
    int num;
    pid_t pid;

    // Create shared memory
    shmid = shmget(SHM_KEY, MAX * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Fork the child process
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process: run child.c
        execl("./child", "child", NULL);
        perror("execl");
        exit(1);
    } else {
        // Parent process: wait for child to finish
        wait(NULL);

        // Attach to shared memory
        shm_ptr = (int *) shmat(shmid, NULL, 0);
        if (shm_ptr == (int *) -1) {
            perror("shmat");
            exit(1);
        }

        // Retrieve number of Fibonacci numbers
        num = shm_ptr[0];
        print_fib(shm_ptr + 1, num);

        // Detach from shared memory
        if (shmdt(shm_ptr) < 0) {
            perror("shmdt");
            exit(1);
        }

        // Remove the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) < 0) {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}

void print_fib(int *p, int n) {
    int i;
    printf("Fibonacci series:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
}
