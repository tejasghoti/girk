#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num < 2)
        return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Function to generate first n prime numbers
void generatePrimes(int n) {
    int count = 0, num = 2;
    printf("Prime sequence: ");
    //fflush(stdout); // flush buffer so output appears immediately
    while (count < n) {
        if (isPrime(num)) {
            printf("%d ", num);
            fflush(stdout);
            count++;
        }
        num++;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // --- Step 1: Validate command-line argument count ---
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // --- Step 2: Validate that input is numeric using strtol() ---
    char *endptr;
    errno = 0; // reset errno before calling strtol()
    long n = strtol(argv[1], &endptr, 10);

    // Check if entire string was numeric
    if (*endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Error: '%s' is not a valid integer.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Check for valid positive integer
    if (n <= 0) {
        fprintf(stderr, "Error: Please enter a positive integer greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    // --- Step 3: Create child process ---
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    // --- Step 4: Child process ---
    else if (pid == 0) {
        printf("\nChild Process (PID = %d): Generating first %ld prime numbers...\n", getpid(), n);
        generatePrimes((int)n);
        printf("Child Process (PID = %d): Completed prime generation.\n", getpid());
        fflush(stdout);
        exit(EXIT_SUCCESS);
    }

    // --- Step 5: Parent process ---
    else {
        printf("Parent Process (PID = %d): Waiting for child to complete...\n", getpid());
        wait(NULL);
        printf("Parent Process (PID = %d): Child completed. Exiting now.\n", getpid());
    }

    return 0;
}
/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ gcc fork2.3.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ ./out
Usage: ./out <positive integer>
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ ./out 10
Parent Process (PID = 12084): Waiting for child to complete...

Child Process (PID = 12085): Generating first 10 prime numbers...
Prime sequence: 2 3 5 7 11 13 17 19 23 29 
Child Process (PID = 12085): Completed prime generation.
Parent Process (PID = 12084): Child completed. Exiting now.
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ ./out -10
Error: Please enter a positive integer greater than 0.
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ ./out 0
Error: Please enter a positive integer greater than 0.
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ ./out 9999999999999999999999999999999999999999999999999
Error: '9999999999999999999999999999999999999999999999999' is not a valid integer.
*/
