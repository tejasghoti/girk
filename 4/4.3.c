#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define FILE_NAME "shared.txt"

// Mutex for file access
pthread_mutex_t fileLock;

// Binary semaphores
sem_t valueReady;     // Producer → Consumer
sem_t valueConsumed;  // Consumer → Producer

// Producer thread
void* producer_file(void* arg) {
    while(1) {
        sem_wait(&valueConsumed);       // Wait until previous value is consumed
        pthread_mutex_lock(&fileLock);

        int num = rand() % 10;          // Generate number 0-9
        FILE* fp = fopen(FILE_NAME, "w");
        fprintf(fp, "%d", num);
        fclose(fp);

        printf("Producer produced: %d\n", num);

        pthread_mutex_unlock(&fileLock);
        sem_post(&valueReady);          // Notify consumer

        usleep((rand() % 100) * 1000);  // Sleep 0–100 ms
    }
}

// Consumer thread
void* consumer_file(void* arg) {
    char buffer[10];
    while(1) {
        sem_wait(&valueReady);          // Wait for producer to produce
        pthread_mutex_lock(&fileLock);

        FILE* fp = fopen(FILE_NAME, "r");
        fgets(buffer, sizeof(buffer), fp);
        fclose(fp);

        int num = atoi(buffer);
        printf("Consumer consumed: %d\n", num);

        pthread_mutex_unlock(&fileLock);
        sem_post(&valueConsumed);       // Notify producer
    }
}

int main() {
    srand(time(NULL));

    pthread_t prod, cons;

    pthread_mutex_init(&fileLock, NULL);
    sem_init(&valueReady, 0, 0);
    sem_init(&valueConsumed, 0, 1);

    pthread_create(&prod, NULL, producer_file, NULL);
    pthread_create(&cons, NULL, consumer_file, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
