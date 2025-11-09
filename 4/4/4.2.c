#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NUM_STUDENTS 6
#define NUM_CHAIRS 3
#define SIMULATION_TIME 20   // Run for 20 seconds

int waiting = 0;
int running = 1;

sem_t taSleep, studentReady;
pthread_mutex_t chairLock;

void *student(void *id)
{
    int sid = *(int*)id;

    while (running)
    {
        sleep(rand() % 5);

        pthread_mutex_lock(&chairLock);

        if (waiting < NUM_CHAIRS)
        {
            waiting++;
            printf("Student %d waiting | Chairs filled: %d\n", sid, waiting);
            sem_post(&studentReady);
            pthread_mutex_unlock(&chairLock);

            // if TA ends before this student gets help, exit
            if (!running) break;

            sem_wait(&taSleep);
            if (!running) break;

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

    pthread_exit(NULL);
}

void *ta(void *arg)
{
    while (running)
    {
        // Use trywait to avoid blocking forever
        if (sem_trywait(&studentReady) == 0)
        {
            pthread_mutex_lock(&chairLock);
            waiting--;
            pthread_mutex_unlock(&chairLock);

            printf("TA awake 👨‍🏫 Helping next student...\n");
            sem_post(&taSleep);
            sleep(2);
            printf("TA finished, checking next student...\n");
        }
        else
        {
            printf("TA sleeping 😴 ...\n");
            sleep(1);
        }
    }

    pthread_exit(NULL);
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

    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        id[i] = i + 1;
        pthread_create(&students[i], NULL, student, &id[i]);
    }

    sleep(SIMULATION_TIME);
    running = 0;
    printf("\n⏰ Office hours over! TA and students going home...\n");

    // 🔹 Wake up any threads blocked in sem_wait()
    for (int i = 0; i < NUM_STUDENTS; i++)
        sem_post(&taSleep);         // wake up students waiting for TA
    sem_post(&studentReady);         // wake up TA waiting for a student

    pthread_join(taThread, NULL);
    for (int i = 0; i < NUM_STUDENTS; i++)
        pthread_join(students[i], NULL);

    sem_destroy(&taSleep);
    sem_destroy(&studentReady);
    pthread_mutex_destroy(&chairLock);

    printf("✅ Simulation ended. Resources cleaned up successfully.\n");

    return 0;
}
/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/4$ gcc 4.2.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/4$ ./out
TA sleeping 😴 ...
Student 1 waiting | Chairs filled: 1
TA sleeping 😴 ...
Student 6 waiting | Chairs filled: 2
Student 2 waiting | Chairs filled: 3
TA awake 👨‍🏫 Helping next student...
TA helping student 1 ✅
Student 5 waiting | Chairs filled: 3
No chair 🚫 Student 4 will come back later
Student 1 done ✔
No chair 🚫 Student 3 will come back later
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
TA helping student 6 ✅
Student 1 waiting | Chairs filled: 3
Student 6 done ✔
No chair 🚫 Student 4 will come back later
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
TA helping student 2 ✅
Student 4 waiting | Chairs filled: 3
Student 2 done ✔
No chair 🚫 Student 3 will come back later
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
Student 6 waiting | Chairs filled: 3
TA helping student 5 ✅
Student 5 done ✔
No chair 🚫 Student 2 will come back later
No chair 🚫 Student 2 will come back later
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
TA helping student 1 ✅
Student 2 waiting | Chairs filled: 3
Student 1 done ✔
No chair 🚫 Student 3 will come back later
No chair 🚫 Student 3 will come back later
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
TA helping student 4 ✅
Student 5 waiting | Chairs filled: 3
Student 4 done ✔
No chair 🚫 Student 1 will come back later
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
TA helping student 6 ✅
Student 4 waiting | Chairs filled: 3
Student 6 done ✔
No chair 🚫 Student 3 will come back later
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
TA helping student 2 ✅
Student 1 waiting | Chairs filled: 3
No chair 🚫 Student 6 will come back later
No chair 🚫 Student 3 will come back later
No chair 🚫 Student 3 will come back later
Student 2 done ✔
TA finished, checking next student...
TA awake 👨‍🏫 Helping next student...
TA helping student 5 ✅
Student 3 waiting | Chairs filled: 3
Student 5 done ✔
No chair 🚫 Student 6 will come back later
No chair 🚫 Student 6 will come back later

⏰ Office hours over! TA and students going home...
TA finished, checking next student...
No chair 🚫 Student 2 will come back later
No chair 🚫 Student 5 will come back later
No chair 🚫 Student 6 will come back later
✅ Simulation ended. Resources cleaned up successfully.
*/
