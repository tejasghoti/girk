#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXP 50
#define MAXSEG 200

struct process {
    char name[10];
    int at, bt, ct, tat, wt;
    int completed;
};

struct seg {           // Gantt chart segment
    char name[12];
    int start;
    int end;
};

void sortByArrival(struct process p[], int n) {
    struct process tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                tmp = p[j]; p[j] = p[j + 1]; p[j + 1] = tmp;
            }
}

/* FCFS with idle segments and proper time markers */
void fcfs(struct process p[], int n) {
    int time = 0;
    int total_wt = 0, total_tat = 0;
    struct seg S[MAXSEG];
    int segc = 0;

    // initialize
    for (int i = 0; i < n; i++) { p[i].completed = 0; p[i].ct = p[i].tat = p[i].wt = 0; }

    for (int i = 0; i < n; i++) {
        if (p[i].at > time) {
            // idle from time to p[i].at
            strcpy(S[segc].name, "IDLE");
            S[segc].start = time;
            S[segc].end = p[i].at;
            segc++;
            time = p[i].at;
        }
        // schedule process i
        strcpy(S[segc].name, p[i].name);
        S[segc].start = time;
        time += p[i].bt;
        S[segc].end = time;
        segc++;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Print Gantt
    printf("\nGANTT CHART:\n ");
    printf(" ");
    for (int i = 0; i < segc; i++) {
        printf("__________");
    }
    printf("\n|");
    for (int i = 0; i < segc; i++) {
        int width = S[i].end - S[i].start;
        // print centered name in approx fixed box width
        printf(" %6s |", S[i].name);
    }
    printf("\n ");
    printf(" ");
    for (int i = 0; i < segc; i++) {
        printf("__________");
    }
    printf("\n");

    // Print time markers
    for (int i = 0; i < segc; i++) {
        printf("%-10d", S[i].start);
    }
    printf("%d\n", S[segc-1].end);

    // Process table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAverage Waiting Time for FCFS = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time for FCFS = %.2f\n", (float)total_tat / n);
}

/* SJF (Non-preemptive) with idle segments and proper Gantt times */
void sjf(struct process p[], int n) {
    int completed = 0;
    int time = 0;
    int total_wt = 0, total_tat = 0;
    struct seg S[MAXSEG];
    int segc = 0;

    // reset
    for (int i = 0; i < n; i++) { p[i].completed = 0; p[i].ct = p[i].tat = p[i].wt = 0; }

    // Keep going until all processes completed
    while (completed < n) {
        int idx = -1;
        int minbt = 1e9;

        // find process with smallest bt among arrived & incomplete
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time) {
                if (p[i].bt < minbt) {
                    minbt = p[i].bt;
                    idx = i;
                } else if (p[i].bt == minbt) {
                    // tie-breaker: earlier arrival or lexicographic name (stable)
                    if (p[i].at < p[idx].at) idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU idle until next arrival
            int nextArrival = 1e9;
            for (int i = 0; i < n; i++)
                if (!p[i].completed && p[i].at < nextArrival)
                    nextArrival = p[i].at;
            // create single IDLE segment [time, nextArrival]
            if (nextArrival > time) {
                strcpy(S[segc].name, "IDLE");
                S[segc].start = time;
                S[segc].end = nextArrival;
                segc++;
                time = nextArrival;
                continue;
            }
        } else {
            // schedule idx from time to time + bt
            strcpy(S[segc].name, p[idx].name);
            S[segc].start = time;
            time += p[idx].bt;
            S[segc].end = time;
            segc++;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            completed++;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        }
    }

    // Print Gantt
    printf("\nGANTT CHART:\n ");
    printf(" ");
    for (int i = 0; i < segc; i++) {
        printf("__________");
    }
    printf("\n|");
    for (int i = 0; i < segc; i++) {
        printf(" %6s |", S[i].name);
    }
    printf("\n ");
    printf(" ");
    for (int i = 0; i < segc; i++) {
        printf("__________");
    }
    printf("\n");

    // Print time markers
    for (int i = 0; i < segc; i++)
        printf("%-10d", S[i].start);
    printf("%d\n", S[segc-1].end);

    // Process table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);

    printf("\nAverage Waiting Time for SJF = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time for SJF = %.2f\n", (float)total_tat / n);
}

int main() {
    struct process p[MAXP];
    int n, choice;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAXP) {
        printf("Invalid number of processes.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("Process name: ");
        scanf("%s", p[i].name);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    // Sort by arrival so both algorithms start from arrival order
    sortByArrival(p, n);

    while (1) {
        printf("\n\n--- CPU SCHEDULING MENU ---\n");
        printf("1. FCFS\n2. SJF (Non-preemptive)\n3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                fcfs(p, n);
                break;
            case 2:
                sjf(p, n);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/3$ ./out
Enter the number of processes: 4
Process name: p1
Arrival Time: 1
Burst Time: 3
Process name: p2
Arrival Time: 2
Burst Time: 4
Process name: p3
Arrival Time: 1
Burst Time: 2
Process name: p4
Arrival Time: 4
Burst Time: 4


--- CPU SCHEDULING MENU ---
1. FCFS
2. SJF (Non-preemptive)
3. Exit
Enter your choice: 2

GANTT CHART:
  __________________________________________________
|   IDLE |     p3 |     p1 |     p2 |     p4 |
  __________________________________________________
0         1         3         6         10        14

Process	AT	BT	CT	TAT	WT
p1	1	3	6	5	2
p3	1	2	3	2	0
p2	2	4	10	8	4
p4	4	4	14	10	6

Average Waiting Time for SJF = 3.00
Average Turnaround Time for SJF = 6.25


--- CPU SCHEDULING MENU ---
1. FCFS
2. SJF (Non-preemptive)
3. Exit
Enter your choice: 1 

GANTT CHART:
  __________________________________________________
|   IDLE |     p1 |     p3 |     p2 |     p4 |
  __________________________________________________
0         1         4         6         10        14

Process	AT	BT	CT	TAT	WT
p1	1	3	4	3	0
p3	1	2	6	5	3
p2	2	4	10	8	4
p4	4	4	14	10	6

Average Waiting Time for FCFS = 3.25
Average Turnaround Time for FCFS = 6.50


--- CPU SCHEDULING MENU ---
1. FCFS
2. SJF (Non-preemptive)
3. Exit
Enter your choice: 3
*/
