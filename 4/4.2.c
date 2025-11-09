#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_STUDENTS 6
#define NUM_CHAIRS 3

int waiting = 0;
sem_t taSleep, studentReady;
pthread_mutex_t chairLock;

void *student(void *id)
{
    int sid = *(int*)id;

    while(1)
    {
        sleep(rand() % 5);

        pthread_mutex_lock(&chairLock);

        if(waiting < NUM_CHAIRS)
        {
            waiting++;
            printf("Student %d waiting | Chairs filled: %d\n", sid, waiting);
            sem_post(&studentReady);
            pthread_mutex_unlock(&chairLock);

            sem_wait(&taSleep);
            printf("TA helping student %d ✅\n", sid);
            sleep(1);
            printf("Student %d done ✔\n", sid);
        }
        else
        {
            printf("No chair 🚫 Student %d will come back later\n", sid);
            pthread_mutex_unlock(&chairLock);
        }
    }
}

void *ta(void *arg)
{
    while(1)
    {
        sem_wait(&studentReady);

        pthread_mutex_lock(&chairLock);
        waiting--;
        pthread_mutex_unlock(&chairLock);

        printf("TA awake 👨‍🏫 Helping next student...\n");
        sem_post(&taSleep);
        sleep(2);
        printf("TA finished, checking next student...\n");
    }
}

int main()
{
    srand(time(NULL));
    pthread_t taThread, students[NUM_STUDENTS];
    int id[NUM_STUDENTS];

    sem_init(&taSleep, 0, 0);
    sem_init(&studentReady, 0, 0);
    pthread_mutex_init(&chairLock, NULL);

    pthread_create(&taThread, NULL, ta, NULL);

    for(int i = 0; i < NUM_STUDENTS; i++)
    {
        id[i] = i+1;
        pthread_create(&students[i], NULL, student, &id[i]);
    }

    pthread_join(taThread, NULL);
    for(int i = 0; i < NUM_STUDENTS; i++)
        pthread_join(students[i], NULL);

    return 0;
}
