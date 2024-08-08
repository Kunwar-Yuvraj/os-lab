#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 10

int buf[BUF_SIZE];
int idx = 0;

sem_t empty, full;
pthread_mutex_t mtx;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 20; i++) {
        item = i;
        sem_wait(&empty);
        pthread_mutex_lock(&mtx);
        buf[idx++] = item;
        printf("Produced: %d\n", item);
        pthread_mutex_unlock(&mtx);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 20; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mtx);
        item = buf[--idx];
        printf("Consumed: %d\n", item);
        pthread_mutex_unlock(&mtx);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUF_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mtx, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mtx);

    return 0;
}
