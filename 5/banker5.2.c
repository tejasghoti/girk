#include <stdio.h>

int main() {
    int n, m;

    FILE *fp = fopen("state.txt", "r");
    if (!fp) {
        printf("Error: Cannot open state.txt\n");
        return 1;
    }

    char line[100];

    // Read until we find "Number of Processes"
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "Number of Processes %d", &n) == 1) break;
    }

    // Read until we find "Number of Resources"
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "Number of Resources %d", &m) == 1) break;
    }

    if (n <= 0 || m <= 0) {
        printf("❌ Error: Could not read process/resource count properly.\n");
        fclose(fp);
        return 1;
    }

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    int finish[n], safeSeq[n];

    printf("Number of Processes: %d\n", n);
    printf("Number of Resources: %d\n", m);

    // ---------- Read Allocation Matrix ----------
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(fp, "%d", &alloc[i][j]);
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }

    // ---------- Read Max Matrix ----------
    printf("\nMax Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(fp, "%d", &max[i][j]);
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    // ---------- Read Available Vector ----------
    printf("\nAvailable Resources:\n");
    for (int i = 0; i < m; i++) {
        fscanf(fp, "%d", &avail[i]);
        printf("%d ", avail[i]);
    }
    printf("\n");

    fclose(fp);


    // Compute Need
    printf("\nNeed Resources:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j] = max[i][j] - alloc[i][j];
            if(need[i][j]<0){
                need[i][j] *= 0;
            }
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // -------- SAFETY CHECK ---------
    for(int i=0;i<n;i++) finish[i] = 0;

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i=0;i<n;i++) {
            if(finish[i] == 0) {
                int j;
                for(j=0;j<m;j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == m) { // all satisfied
                    for(int k=0;k<m;k++)
                        avail[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found) break;
    }

    if(count == n) {
        printf("\n✅ System is in SAFE state.\nSafe Sequence: ");
        for(int i=0;i<n;i++) printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\n❌ System is in UNSAFE state. Deadlock possible.\n");
    }

    // ===== RESOURCE REQUEST =====
    int reqP;

    printf("\nEnter Process Number requesting resource: ");
    scanf("%d", &reqP);

    // Validate process number
    if(reqP < 0 || reqP >= n) {
        printf("❌ Invalid process number!\n");
        return 0;
    }

    int req[m];

    printf("Enter Request Vector: ");
    for(int i=0;i<m;i++)
        scanf("%d", &req[i]);

    // Check validity
    for(int i=0;i<m;i++) {
        if(req[i] > need[reqP][i]) {
            printf("❌ Error: Request exceeds process need.\n");
            return 0;
        }
        if(req[i] > avail[i]) {
            printf("❌ Resources NOT available. Process must wait.\n");
            return 0;
        }
    }

    // Pretend Allocation
    for(int i=0;i<m;i++) {
        avail[i] -= req[i];
        alloc[reqP][i] += req[i];
        need[reqP][i] -= req[i];
    }

    // Safety check after pretend allocation
    int safeSeqReq[n];
    for(int i=0;i<n;i++) finish[i] = 0;
    count = 0;

    while(count < n) {
        int found = 0;

        for(int i=0;i<n;i++) {
            if(finish[i] == 0) {
                int j;
                for(j=0;j<m;j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == m) {
                    for(int k=0;k<m;k++)
                        avail[k] += alloc[i][k];

                    safeSeqReq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found) break;
    }

    if(count == n) {
        printf("\n✅ Request can be GRANTED safely.\nSafe Sequence: ");
        for(int i=0;i<n;i++) printf("P%d ", safeSeqReq[i]);
        printf("\n");
    } else {
        printf("\n❌ Request CANNOT be granted (Unsafe State).\n");
    }

    return 0;
}

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/5$ gcc banker5.2.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/5$ ./out
Number of Processes: 5
Number of Resources: 4

Allocation Matrix:
3 2 0 0 
0 1 1 2 
2 1 0 0 
0 0 1 0 
2 1 1 1 

Max Matrix:
3 0 1 1 
0 1 1 0 
1 1 0 0 
1 0 0 1 
0 0 0 0 

Available Resources:
1 0 2 1 

Need Resources:
0 0 1 1 
0 0 0 0 
0 0 0 0 
1 0 0 1 
0 0 0 0 

✅ System is in SAFE state.
Safe Sequence: P0 P1 P2 P3 P4 

Enter Process Number requesting resource: 3
Enter Request Vector: 1 0 0 1

✅ Request can be GRANTED safely.
Safe Sequence: P0 P1 P2 P3 P4 
*/
