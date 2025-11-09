#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Shared data (e.g., flight seats available)
int flightSeats = 100;

// Mutex and semaphore
pthread_mutex_t readerCountLock;
sem_t resourceAccess;

int readerCount = 0;

// Reader thread
void* reader(void* arg) {
    int id = *(int*)arg;
    while(1) {
        // Entry section for reader
        pthread_mutex_lock(&readerCountLock);
        readerCount++;
        if(readerCount == 1)
            sem_wait(&resourceAccess); // First reader locks resource
        pthread_mutex_unlock(&readerCountLock);

        // Critical section: reading flight info
        printf("Reader %d is reading flight info: Seats available = %d\n", id, flightSeats);
        sleep(1);

        // Exit section for reader
        pthread_mutex_lock(&readerCountLock);
        readerCount--;
        if(readerCount == 0)
            sem_post(&resourceAccess); // Last reader unlocks resource
        pthread_mutex_unlock(&readerCountLock);

        sleep(rand() % 3); // Random delay before next read
    }
}

// Writer thread
void* writer(void* arg) {
    int id = *(int*)arg;
    while(1) {
        sem_wait(&resourceAccess); // Wait for exclusive access

        // Critical section: updating flight info
        int seatsToBook = rand() % 5 + 1; // Book 1–5 seats
        if(flightSeats >= seatsToBook) {
            flightSeats -= seatsToBook;
            printf("Writer %d booked %d seats | Seats left = %d\n", id, seatsToBook, flightSeats);
        } else {
            printf("Writer %d wanted to book %d seats, but only %d left\n", id, seatsToBook, flightSeats);
        }
        sleep(2);

        sem_post(&resourceAccess); // Release resource
        sleep(rand() % 3);         // Random delay before next booking
    }
}

int main() {
    srand(time(NULL));

    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int r_id[NUM_READERS], w_id[NUM_WRITERS];

    pthread_mutex_init(&readerCountLock, NULL);
    sem_init(&resourceAccess, 0, 1);

    // Create reader threads
    for(int i = 0; i < NUM_READERS; i++) {
        r_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &r_id[i]);
    }

    // Create writer threads
    for(int i = 0; i < NUM_WRITERS; i++) {
        w_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &w_id[i]);
    }

    // Join threads (infinite loops, so program runs continuously)
    for(int i = 0; i < NUM_READERS; i++)
        pthread_join(readers[i], NULL);
    for(int i = 0; i < NUM_WRITERS; i++)
        pthread_join(writers[i], NULL);

    return 0;
}
