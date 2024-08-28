// parent.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>  

int main() {
    int n = 5;
    key_t key = 1234;

    if (fork() == 0) {
        execl("./fibonacci", "fibonacci", NULL);
    }

    wait(NULL);

    int shmid = shmget(key, n * sizeof(int), 0666);
    int *shm_addr = shmat(shmid, NULL, 0);

    printf("Fibonacci series:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", shm_addr[i]);
    }
    printf("\n");

    shmdt(shm_addr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
