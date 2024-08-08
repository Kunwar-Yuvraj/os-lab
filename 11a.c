#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *calc_sum(void *arg) {
    int n = *(int *)arg, sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    printf("Sum: %d\n", sum);
    pthread_exit(NULL);
}

void *calc_fact(void *arg) {
    int n = *(int *)arg, fact = 1;
    for (int i = 1; i <= n; i++) fact *= i;
    printf("Factorial: %d\n", fact);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    pthread_t sum_thread, fact_thread;

    pthread_create(&sum_thread, NULL, calc_sum, &n);
    pthread_create(&fact_thread, NULL, calc_fact, &n);

    pthread_join(sum_thread, NULL);
    pthread_join(fact_thread, NULL);

    return 0;
}
