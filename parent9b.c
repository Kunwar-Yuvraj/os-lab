// parent.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int N = 10; 
    key_t key = 1234;
    int shmid;
    int *shm_addr;

    shmid = shmget(key, N * sizeof(int), IPC_CREAT | 0666);

    if (fork() == 0) {
        execl("./oddgen", "oddgen", NULL);
    }

    wait(NULL);

    shm_addr = (int *)shmat(shmid, NULL, 0);
    for (int i = 0; i < N; i++) {
        printf("%d ", shm_addr[i]);
    }
    printf("\n");

    shmdt(shm_addr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
