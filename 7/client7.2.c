#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

// semaphore wait (P)
void sem_wait(int semid) {
    struct sembuf op = {0, -1, 0};
    semop(semid, &op, 1);
}

int main() {
    key_t key = ftok(".", 75);

    int shmid = shmget(key, 1024, 0666);
    int semid = semget(key, 1, 0666);

    char *msg = shmat(shmid, NULL, 0);

    sem_wait(semid); // wait for server

    printf("Client Read: %s\n", msg);

    shmdt(msg);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, 0);

    return 0;
}

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/7$ ./client
Client Read: helo helo
*/
