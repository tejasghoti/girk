#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble sort function
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Sort the array
    bubbleSort(arr, n);

    printf("\nParent Process (PID=%d): Sorted array: ", getpid());
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
        // ---- CHILD PROCESS ----
        printf("\nChild Process (PID=%d): Executing new program using execve()\n", getpid());

        // Convert integers to strings for passing as command-line arguments
        char *args[n + 3]; // program name + n numbers + key + NULL
        args[0] = "./child"; // executable file name

        for (int i = 0; i < n; i++) {
            char *num = malloc(10);
            sprintf(num, "%d", arr[i]);
            args[i + 1] = num;
        }

        // Ask for element to search
        int key;
        printf("Enter element to search: ");
        scanf("%d", &key);
        char *keyStr = malloc(10);
        sprintf(keyStr, "%d", key);
        args[n + 1] = keyStr;
        args[n + 2] = NULL; // Null terminate argument list

        // Execute the new program
        execve(args[0], args, NULL);

        // execve() replaces current process; this line executes only if execve fails
        perror("execve failed");
        exit(1);
    }

    else {
        // ---- PARENT PROCESS ----
        wait(NULL); // Wait for child to finish
        printf("\nParent Process (PID=%d): Child finished execution.\n", getpid());
    }

    return 0;
}



/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ gcc execv2.2.c -o parent
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ gcc child.c -o child
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/2$ ./parent
Enter number of integers: 5
Enter 5 integers: 5 1 3 2 4

Parent Process (PID=11903): Sorted array: 1 2 3 4 5 

Child Process (PID=11905): Executing new program using execve()
Enter element to search: 3

Child Program (Binary Search):
Received Sorted Array: 1 2 3 4 5 
Element to Search: 3
Element 3 found at position 3

Parent Process (PID=11903): Child finished execution.
*/
