#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIME_QUANTUM 2
#define MAX 10

typedef struct {
    char name[10];
    int arrival, burst, remaining, completion, turnaround, waiting;
} Process;

void findAverage(Process p[], int n, float *avgTAT, float *avgWT) {
    *avgTAT = 0;
    *avgWT = 0;
    for (int i = 0; i < n; i++) {
        *avgTAT += p[i].turnaround;
        *avgWT += p[i].waiting;
    }
    *avgTAT /= n;
    *avgWT /= n;
}

void printTable(Process p[], int n) {
    printf("\n%-8s%-12s%-12s%-12s%-15s%-15s\n",
           "Process", "Arrival", "Burst", "Waiting", "Turnaround", "Completion");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-8s%-12d%-12d%-12d%-15d%-15d\n",
               p[i].name, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround, p[i].completion);
    }
}

void fcfs(Process p[], int n) {
    int time = 0;
    float avgTAT, avgWT;

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].arrival > p[j].arrival) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    printf("\nGANTT CHART:\n");
    printf("_________________________\n| ");

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        printf("%s | ", p[i].name);
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    printf("\n_________________________\n");

    // Print time line
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        printf("%d   ", time);
        time += p[i].burst;
    }
    printf("%d\n", time);

    findAverage(p, n, &avgTAT, &avgWT);
    printTable(p, n);
    printf("\nAverage Waiting Time for FCFS: %.2f", avgWT);
    printf("\nAverage Turnaround Time for FCFS: %.2f\n", avgTAT);
}

void roundRobin(Process p[], int n) {
    int completed = 0, time = 0;
    float avgTAT, avgWT;
    int queue[MAX], front = 0, rear = 0;
    int inQueue[MAX] = {0};

    // Reset all fields
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].completion = 0;
    }

    printf("\nGANTT CHART:\n");
    printf("_________________________\n| ");

    while (completed < n) {
        // Add available processes to queue
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && !inQueue[i]) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int idx = queue[front++];
        if (front == rear)
            front = rear = 0;

        int execTime = (p[idx].remaining > TIME_QUANTUM) ? TIME_QUANTUM : p[idx].remaining;
        printf("%s | ", p[idx].name);
        time += execTime;
        p[idx].remaining -= execTime;

        // Add new processes that have arrived during execution
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && !inQueue[i]) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (p[idx].remaining > 0)
            queue[rear++] = idx;
        else {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }

        // Reset queue marker for executed process if completed
        if (p[idx].remaining == 0)
            inQueue[idx] = 0;
    }

    printf("\n_________________________\n");

    // Print timeline
    time = 0;
    printf("0");
    int temp[MAX], tempCount = 0;
    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    // (Optional timeline simplified)
    printf("\n");

    findAverage(p, n, &avgTAT, &avgWT);
    printTable(p, n);
    printf("\nAverage Waiting Time for Round Robin: %.2f", avgWT);
    printf("\nAverage Turnaround Time for Round Robin: %.2f\n", avgTAT);
}

int main() {
    int n, choice;
    Process p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival time and Burst time:\n");
    for (int i = 0; i < n; i++) {
        sprintf(p[i].name, "p%d", i + 1);
        printf("%s: ", p[i].name);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    do {
        printf("\nEnter your choice:\n1. FCFS\n2. Round Robin (time quantum = 2)\n3. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            fcfs(p, n);
            break;
        case 2:
            roundRobin(p, n);
            break;
        case 3:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/3$ ./out
Enter the number of processes: 4
Enter Arrival time and Burst time:
p1: 0
5
p2: 1 4
p3: 2 2
p4: 4 1

Enter your choice:
1. FCFS
2. Round Robin (time quantum = 2)
3. Exit
Choice: 1

GANTT CHART:
_________________________
| p1 | p2 | p3 | p4 | 
_________________________
0   5   9   11   12

Process Arrival     Burst       Waiting     Turnaround     Completion     
---------------------------------------------------------------
p1      0           5           0           5              5              
p2      1           4           4           8              9              
p3      2           2           7           9              11             
p4      4           1           7           8              12             

Average Waiting Time for FCFS: 4.50
Average Turnaround Time for FCFS: 7.50

Enter your choice:
1. FCFS
2. Round Robin (time quantum = 2)
3. Exit
Choice: 2

GANTT CHART:
_________________________
| p1 | p2 | p3 | p1 | p4 | p2 | p1 | 
_________________________
0

Process Arrival     Burst       Waiting     Turnaround     Completion     
---------------------------------------------------------------
p1      0           5           7           12             12             
p2      1           4           6           10             11             
p3      2           2           2           4              6              
p4      4           1           4           5              9              

Average Waiting Time for Round Robin: 4.75
Average Turnaround Time for Round Robin: 7.75

Enter your choice:
1. FCFS
2. Round Robin (time quantum = 2)
3. Exit
Choice: 3
Exiting program.
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/3$ 

*/
