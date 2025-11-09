#include <stdio.h>

struct Process {
    int pid, at, bt, rt, ct, tat, wt, completed;
};

void printTable(struct Process p[], int n) {
    printf("\n---------------------------------------------------------\n");
    printf("| PID | AT | BT | CT | TAT | WT |\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %3d | %2d | %2d | %2d | %3d | %2d |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("---------------------------------------------------------\n");
}

// ---------- FCFS ----------
void FCFS(struct Process p[], int n) {

    // Sorting acc to AT
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- FCFS Scheduling ---\n");
    printf("GANTT CHART:\n");
    printf("\n|");

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("  p%d  |", p[i].pid);
    }

    printf("\n----------------------------------\n");

    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;
        printf("%-7d", time);
        time += p[i].bt;
    }
    printf("%d\n", time);

    printTable(p, n);

    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

// // ---------- SJF NON-PREEMPTIVE ----------
// void SJF_NonPreemptive(struct Process p[], int n) {
//     int completed = 0, time = 0;
//     float total_tat = 0, total_wt = 0;

//     printf("\n--- SJF (Non-Preemptive) Scheduling ---\n");
//     printf("GANTT CHART:\n__\n|");

//     while (completed != n) {
//         int idx = -1, min_bt = 9999;
//         for (int i = 0; i < n; i++) {
//             if (p[i].at <= time && p[i].completed == 0 && p[i].bt < min_bt) {
//                 min_bt = p[i].bt;
//                 idx = i;
//             }
//         }

//         if (idx == -1) {
//             time++;
//             continue;
//         }

//         printf("  p%d  |", p[idx].pid);
//         time += p[idx].bt;
//         p[idx].ct = time;
//         p[idx].tat = p[idx].ct - p[idx].at;
//         p[idx].wt = p[idx].tat - p[idx].bt;
//         p[idx].completed = 1;
//         total_tat += p[idx].tat;
//         total_wt += p[idx].wt;
//         completed++;
//     }

//     printf("\n---------------------------------------\n0");
//     for (int i = 0; i < n; i++)
//         printf("     %d", p[i].ct);
//     printf("\n");

//     printTable(p, n);

//     printf("Average Waiting Time = %.2f\n", total_wt / n);
//     printf("Average Turnaround Time = %.2f\n", total_tat / n);
// }


void SJF_NonPreemptive(struct Process p[], int n) {
    int completed = 0, time = 0;
    float total_tat = 0, total_wt = 0;
    int execOrder[n], eo = 0; // To store execution order

    // Initialize completed flag
    for (int i = 0; i < n; i++)
        p[i].completed = 0;

    printf("\n--- SJF (Non-Preemptive) Scheduling ---\n");
    printf("GANTT CHART:\n\n|");

    while (completed != n) {
        int idx = -1, min_bt = 9999;

        // Find process with minimum burst time among arrived & not completed
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0 && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        // If no process is available, increment time
        if (idx == -1) {
            time++;
            continue;
        }

        // Execute selected process
        printf("  P%d  |", p[idx].pid);
        // Store the process in execution order
        execOrder[eo++] = idx;

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;

        total_tat += p[idx].tat;
        total_wt += p[idx].wt;
        completed++;
    }

    // Print Gantt chart time labels correctly
    printf("\n------------------------------------------------------\n");
    int start_time = 0;
    printf("0");
    for (int i = 0; i < eo; i++) {
        printf("%-7d", p[execOrder[i]].ct);
    }
    printf("\n");

    // Print detailed table
    printTable(p, n);

    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}


// ---------- SJF PREEMPTIVE ----------
// void SJF_Preemptive(struct Process p[], int n) {
//     int completed = 0, time = 0, idx = -1, min_rt;
//     float total_tat = 0, total_wt = 0;

//     printf("\n--- SJF (Preemptive) Scheduling ---\n");
//     printf("GANTT CHART:\n__\n|");

//     while (completed != n) {
//         min_rt = 9999;
//         idx = -1;

//         // Finding process with arrived & not completed & least remaining time & positive remaining time
//         for (int i = 0; i < n; i++) {
//             if (p[i].at <= time && p[i].completed == 0 && p[i].rt < min_rt && p[i].rt > 0) {
//                 min_rt = p[i].rt;
//                 idx = i;
//             }
//         }

//         if (idx == -1) {
//             time++;
//             continue;
//         }

//         printf("  p%d  |", p[idx].pid);
//         p[idx].rt--;
//         time++;

//         if (p[idx].rt == 0) {
//             p[idx].completed = 1;
//             p[idx].ct = time;
//             p[idx].tat = p[idx].ct - p[idx].at;
//             p[idx].wt = p[idx].tat - p[idx].bt;
//             total_tat += p[idx].tat;
//             total_wt += p[idx].wt;
//             completed++;
//         }
//     }

//     printf("\n--------------------------------------\n");
//     printf("0     %d\n", time);

//     printTable(p, n);

//     printf("Average Waiting Time = %.2f\n", total_wt / n);
//     printf("Average Turnaround Time = %.2f\n", total_tat / n);
// }


void SJF_Preemptive(struct Process p[], int n) {
    int completed = 0, time = 0, prev = -1;
    float total_tat = 0, total_wt = 0;

    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        p[i].completed = 0;
    }

    printf("\n--- SJF (Preemptive) Scheduling ---\n");
    printf("GANTT CHART:\n\n|");

    while (completed != n) {
        int idx = -1;
        int min_rt = 9999;

        // Find process with minimum remaining time among arrived ones
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0 && p[i].rt < min_rt && p[i].rt > 0) {
                min_rt = p[i].rt;
                idx = i;
            }
        }

        // If no process has arrived yet
        if (idx == -1) {
            time++;
            continue;
        }

        // Print process only if context switch occurs
        if (prev != idx) {
            printf("  P%d  |", p[idx].pid);
            prev = idx;
        }

        // Run process for 1 unit
        p[idx].rt--;
        time++;

        // If process completed
        if (p[idx].rt == 0) {
            p[idx].completed = 1;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            completed++;
        }
    }

    printf("\n------------------------------------------------------\n");
    printf("0     %d\n", time);

    printTable(p, n);

    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}


// ---------- ROUND ROBIN ----------

// void RoundRobin(struct Process p[], int n, int tq) {
//     int time = 0, done;
//     float total_tat = 0, total_wt = 0;

//     printf("\n--- Round Robin (Time Quantum = %d) ---\n", tq);
//     printf("GANTT CHART:\n__\n|");

//     while (1) {
//         done = 1;
//         for (int i = 0; i < n; i++) {
//             if (p[i].rt > 0 && p[i].at <= time) {
//                 done = 0;
//                 printf("  p%d  |", p[i].pid);

//                 if (p[i].rt > tq) {
//                     time += tq;
//                     p[i].rt -= tq;
//                 } else {
//                     time += p[i].rt;
//                     p[i].ct = time;
//                     p[i].rt = 0;
//                     p[i].tat = p[i].ct - p[i].at;
//                     p[i].wt = p[i].tat - p[i].bt;
//                     total_tat += p[i].tat;
//                     total_wt += p[i].wt;
//                 }
//             }
//         }
//         if (done)
//             break;
//     }

//     printf("\n-----------------------------------------\n");
//     printf("0     %d\n", time);

//     printTable(p, n);

//     printf("Average Waiting Time = %.2f\n", total_wt / n);
//     printf("Average Turnaround Time = %.2f\n", total_tat / n);
// }


void RoundRobin(struct Process p[], int n, int tq) {
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
    int queue[100], front = 0, rear = 0; // Simple queue for ready processes
    int visited[100] = {0};

    printf("\n--- Round Robin (Time Quantum = %d) ---\n", tq);
    printf("GANTT CHART:\n\n");
    printf("0");

    // Initially add first process that has arrived at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed != n) {
        if (front == rear) { // No process ready yet
            time++;
            for (int i = 0; i < n; i++) {
                //arrived and not visited
                if (p[i].at <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        printf(" | P%d |", p[idx].pid);

        if (p[idx].rt > tq) {
            time += tq;
            p[idx].rt -= tq;
        } else {
            time += p[idx].rt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            p[idx].rt = 0;
            completed++;
        }

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If process not finished, push it back
        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        }

        printf(" %d", time);
    }

    printf("\n----------------------------------------------------\n");

    printTable(p, n);

    printf("Average Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}


// ---------- MAIN ----------
int main() {
    int n, choice;
    struct Process p[10];

    printf("Enter number of processes : ");
    scanf("%d", &n);

    //Taking input for AT & BT
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    while (1) {
        for (int i = 0; i < n; i++) // reset before each run
        {
            p[i].rt = p[i].bt;
            p[i].completed = 0;
            p[i].ct = p[i].tat = p[i].wt = 0;
        }

        printf("\n===== CPU SCHEDULING MENU =====\n");
        printf("1. FCFS\n");
        printf("2. SJF (Non-Preemptive)\n");
        printf("3. SJF (Preemptive)\n");
        printf("4. Round Robin (Preemptive)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FCFS(p, n);
                break;
            case 2:
                SJF_NonPreemptive(p, n);
                break;
            case 3:
                SJF_Preemptive(p, n);
                break;
            case 4:
                RoundRobin(p, n, 2);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}