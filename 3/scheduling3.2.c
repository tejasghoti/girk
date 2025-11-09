#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

struct Process {
    char name[10];
    int at, bt, ct, tat, wt;
    int rt; // remaining time
    int completed;
};

struct Gantt {
    char name[10];
    int start, end;
};

// ---------- Sort by Arrival Time ----------
void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
}

// ---------- FCFS Scheduling ----------
void fcfs(struct Process p[], int n) {
    struct Gantt g[MAX];
    int time = 0, gi = 0;
    float totalWT = 0, totalTAT = 0;

    sortByArrival(p, n);

    printf("\n========= FCFS Scheduling =========\n");

    for (int i = 0; i < n; i++) {
        if (time < p[i].at) { // Idle time
            strcpy(g[gi].name, "IDLE");
            g[gi].start = time;
            time = p[i].at;
            g[gi].end = time;
            gi++;
        }
        strcpy(g[gi].name, p[i].name);
        g[gi].start = time;
        time += p[i].bt;
        g[gi].end = time;
        gi++;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    // --- Gantt Chart ---
    printf("\nGANTT CHART:\n ");
    for (int i = 0; i < gi; i++) printf("-----------");
    printf("\n|");
    for (int i = 0; i < gi; i++) printf(" %-8s |", g[i].name);
    printf("\n ");
    for (int i = 0; i < gi; i++) printf("-----------");
    printf("\n");
    for (int i = 0; i < gi; i++) printf("%-11d", g[i].start);
    printf("%d\n", g[gi - 1].end);

    // --- Process Table ---
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);
}

// ---------- SJF (Preemptive) / SRTF ----------
void sjf_preemptive(struct Process p[], int n) {
    struct Gantt g[MAX * 10];
    int time = 0, completed = 0, gi = 0;
    float totalWT = 0, totalTAT = 0;

    sortByArrival(p, n);
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    int prev = -1;

    while (completed < n) {
        int idx = -1;
        int minRT = 1e9;

        // find process with smallest remaining time among arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1) {
            // CPU idle
            if (prev != -2) {
                strcpy(g[gi].name, "IDLE");
                g[gi].start = time;
                prev = -2;
                gi++;
            }
            time++;
            g[gi - 1].end = time;
        } else {
            if (prev != idx) {
                strcpy(g[gi].name, p[idx].name);
                g[gi].start = time;
                prev = idx;
                gi++;
            }

            p[idx].rt--;
            time++;
            g[gi - 1].end = time;

            if (p[idx].rt == 0) {
                p[idx].completed = 1;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
                completed++;
            }
        }
    }

    // --- Gantt Chart ---
    printf("\n========= SJF (Preemptive) Scheduling =========\n");
    printf("\nGANTT CHART:\n ");
    for (int i = 0; i < gi; i++) printf("-----------");
    printf("\n|");
    for (int i = 0; i < gi; i++) printf(" %-8s |", g[i].name);
    printf("\n ");
    for (int i = 0; i < gi; i++) printf("-----------");
    printf("\n");
    for (int i = 0; i < gi; i++) printf("%-11d", g[i].start);
    printf("%d\n", g[gi - 1].end);

    // --- Process Table ---
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);
}

int main() {
    struct Process p[MAX];
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess name: ");
        scanf("%s", p[i].name);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    do {
        printf("\n\nEnter your choice:\n1. FCFS\n2. SJF (Preemptive)\n3. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            fcfs(p, n);
            break;
        case 2:
            sjf_preemptive(p, n);
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/3$ gedit scheduling3.2.c
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/3$ gcc scheduling3.2.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/3$ ./out
Enter the number of processes: 4

Process name: 1
Arrival Time: 0
Burst Time: 5

Process name: 2
Arrival Time: 1
Burst Time: 3

Process name: 3
Arrival Time: 2
Burst Time: 4

Process name: 4
Arrival Time: 4
Burst Time: 1


Enter your choice:
1. FCFS
2. SJF (Preemptive)
3. Exit
Choice: 1

========= FCFS Scheduling =========

GANTT CHART:
 --------------------------------------------
| 1        | 2        | 3        | 4        |
 --------------------------------------------
0          5          8          12         13

Process	AT	BT	CT	TAT	WT
1	0	5	5	5	0
2	1	3	8	7	4
3	2	4	12	10	6
4	4	1	13	9	8

Average Waiting Time = 4.50
Average Turnaround Time = 7.75


Enter your choice:
1. FCFS
2. SJF (Preemptive)
3. Exit
Choice: 2

========= SJF (Preemptive) Scheduling =========

GANTT CHART:
 -------------------------------------------------------
| 1        | 2        | 4        | 1        | 3        |
 -------------------------------------------------------
0          1          4          5          9          13

Process	AT	BT	CT	TAT	WT
1	0	5	9	9	4
2	1	3	4	3	0
3	2	4	13	11	7
4	4	1	5	1	0

Average Waiting Time = 2.75
Average Turnaround Time = 6.00


Enter your choice:
1. FCFS
2. SJF (Preemptive)
3. Exit
Choice: 3
Exiting...
*/
