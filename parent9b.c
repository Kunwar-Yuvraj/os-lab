// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_KEY 1234
#define MAX 100

int main() {
    int shmid, *shm_ptr, num;
    pid_t pid;

    // Create or get shared memory
    shmid = shmget(SHM_KEY, MAX * sizeof(int), 0666);

    // Fork and execute child
    if ((pid = fork()) == 0) {
        execl("./child", "child", NULL);
        perror("execl");
        exit(1);
    }
    wait(NULL);

    // Attach shared memory
    shm_ptr = (int *)shmat(shmid, NULL, 0);

    // Read number of odd numbers
    num = shm_ptr[0];
    printf("Odd numbers:\n");
    for (int i = 1; i <= num; i++) printf("%d ", shm_ptr[i]);
    printf("\n");

    // Cleanup
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
