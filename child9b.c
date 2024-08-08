// child.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define MAX 100

int main() {
    int shmid, *shm_ptr, num;

    // Get shared memory
    shmid = shmget(SHM_KEY, MAX * sizeof(int), IPC_CREAT | 0666);
    shm_ptr = (int *)shmat(shmid, NULL, 0);

    // Get number of odd numbers
    printf("Enter number of odd numbers to generate: ");
    scanf("%d", &num);

    // Write number of odd numbers as the first value
    shm_ptr[0] = num;

    // Generate and store odd numbers
    for (int i = 1; i <= num; i++) shm_ptr[i] = 2 * (i - 1) + 1;

    // Detach and exit
    shmdt(shm_ptr);
    return 0;
}
