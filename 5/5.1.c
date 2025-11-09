#include <stdio.h>

int main() {
    int n, m; // n = number of processes, m = number of resources
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int finish[10] = {0}, safeSeq[10];
    int i, j, k, count = 0;

    // Input allocation matrix
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum matrix
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate need matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Banker's Algorithm
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) { // process not yet completed
                int canRun = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    // Add process resources to available
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("\nSystem is in UNSAFE state!\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state.\n");
    printf("Safe Sequence: ");
    for (i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 0;
}
