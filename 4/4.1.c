#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define PRODUCE_COUNT 10

int pizzas = 0;
sem_t empty, full;
pthread_mutex_t lock;

void *producer(void *arg)
{
    for (int i = 0; i < PRODUCE_COUNT; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&lock);

        pizzas++;
        printf("Simpson baked pizza 🍕 | Pizzas on counter = %d\n", pizzas);
        fflush(stdout);

        pthread_mutex_unlock(&lock);
        sem_post(&full);
        sleep(1);
    }

    printf("Simpson done baking! 🧑‍🍳\n");
    fflush(stdout);
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    for (int i = 0; i < PRODUCE_COUNT; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&lock);

        pizzas--;
        printf("Joey ate pizza 😋 | Pizzas left = %d\n", pizzas);
        fflush(stdout);

        pthread_mutex_unlock(&lock);
        sem_post(&empty);
        sleep(2);
    }

    printf("Joey is full now! 😴\n");
    fflush(stdout);
    pthread_exit(NULL);
}

int main()
{
    pthread_t simpson, joey;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&simpson, NULL, producer, NULL);
    pthread_create(&joey, NULL, consumer, NULL);

    pthread_join(simpson, NULL);
    pthread_join(joey, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    printf("\nAll threads finished. Resources cleaned up successfully ✅\n");
    fflush(stdout);

    return 0;
}

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/4$ gcc 4.1.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/4$ ./out
Simpson baked pizza 🍕 | Pizzas on counter = 1
Joey ate pizza 😋 | Pizzas left = 0
Simpson baked pizza 🍕 | Pizzas on counter = 1
Joey ate pizza 😋 | Pizzas left = 0
Simpson baked pizza 🍕 | Pizzas on counter = 1
Simpson baked pizza 🍕 | Pizzas on counter = 2
Joey ate pizza 😋 | Pizzas left = 1
Simpson baked pizza 🍕 | Pizzas on counter = 2
Simpson baked pizza 🍕 | Pizzas on counter = 3
Joey ate pizza 😋 | Pizzas left = 2
Simpson baked pizza 🍕 | Pizzas on counter = 3
Simpson baked pizza 🍕 | Pizzas on counter = 4
Joey ate pizza 😋 | Pizzas left = 3
Simpson baked pizza 🍕 | Pizzas on counter = 4
Simpson baked pizza 🍕 | Pizzas on counter = 5
Joey ate pizza 😋 | Pizzas left = 4
Simpson done baking! 🧑‍🍳
Joey ate pizza 😋 | Pizzas left = 3
Joey ate pizza 😋 | Pizzas left = 2
Joey ate pizza 😋 | Pizzas left = 1
Joey ate pizza 😋 | Pizzas left = 0
Joey is full now! 😴

All threads finished. Resources cleaned up successfully ✅
*/
