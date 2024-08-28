// fibonacci.c
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void generate_fibonacci(int *shm_addr, int n) {
    if (n <= 0) return;
    shm_addr[0] = 0;
    if (n > 1) shm_addr[1] = 1;
    for (int i = 2; i < n; i++) {
        shm_addr[i] = shm_addr[i - 1] + shm_addr[i - 2];
    }
}

void generate_odd(int *shm_addr, int n){
    for (int i = 0; i < n; i++){
        shm_addr[i] = 2*i + 1;
    }
}

int main() {
    int n = 100;
    key_t key = 1234;
    int shmid = shmget(key, n * sizeof(int), IPC_CREAT | 0666);
    int *shm_addr = shmat(shmid, NULL, 0);
    // generate_fibonacci(shm_addr, n);
    generate_odd(shm_addr, n);
    shmdt(shm_addr);
    return 0;
}
