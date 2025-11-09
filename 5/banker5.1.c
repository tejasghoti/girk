#include <stdio.h>

int main() {
    int n, m; // n = number of processes, m = number of resources
    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], finish[10], safeSeq[10];
    int i, j, k, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }

    // Input Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix = Max - Alloc
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    // Initialize finish[] to 0
    for (i = 0; i < n; i++)
        finish[i] = 0;

    // Safety Algorithm
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    // process can be safely executed
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("\nSystem is in UNSAFE state ❌\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state ✅\nSafe Sequence is: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");
    return 0;
}
/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/5$ gedit banker5.1.c
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/5$ gcc banker5.1.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/5$ ./out
Enter number of processes: 5
Enter number of resources: 3

Enter Allocation Matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Enter Maximum Matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Enter Available Resources:
3 3 2

Need Matrix:
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 

System is in SAFE state ✅
Safe Sequence is: P1 P3 P4 P0 P2 
*/
