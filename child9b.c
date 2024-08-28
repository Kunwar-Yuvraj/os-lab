// oddgen.c
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int N = 10; // Number of odd numbers
    key_t key = 1234;
    int shmid;
    int *shm_addr;

    // Attach to shared memory
    shmid = shmget(key, N * sizeof(int), 0666);
    shm_addr = (int *)shmat(shmid, NULL, 0);

    // Generate and write odd numbers to shared memory
    for (int i = 0; i < N; i++) {
        shm_addr[i] = 2 * i + 1;
    }

    // Detach from shared memory
    shmdt(shm_addr);

    return 0;
}
