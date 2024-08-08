#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw;       
pthread_mutex_t mtx; 
int rc = 0; 

void *reader(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 1; i++) {  // Limit to 5 read operations per reader
        pthread_mutex_lock(&mtx);
        rc++;
        if (rc == 1)
            sem_wait(&rw);
        pthread_mutex_unlock(&mtx);

        printf("Reader %d reading\n", id);

        pthread_mutex_lock(&mtx);
        rc--;
        if (rc == 0)
            sem_post(&rw);
        pthread_mutex_unlock(&mtx);

        sleep(1);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 1; i++) {  // Limit to 5 write operations per writer
        sem_wait(&rw);
        printf("Writer %d writing\n", id);
        sem_post(&rw);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t r[5], w[3];
    int ids[5] = {1, 2, 3, 4, 5};
    int i;

    sem_init(&rw, 0, 1);
    pthread_mutex_init(&mtx, NULL);

    for (i = 0; i < 5; i++) pthread_create(&r[i], NULL, reader, &ids[i]);
    for (i = 0; i < 3; i++) pthread_create(&w[i], NULL, writer, &ids[i]);

    for (i = 0; i < 5; i++) pthread_join(r[i], NULL);
    for (i = 0; i < 3; i++) pthread_join(w[i], NULL);

    sem_destroy(&rw);
    pthread_mutex_destroy(&mtx);

    return 0;
}
