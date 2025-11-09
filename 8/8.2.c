#include <stdio.h>
#include <stdlib.h>

#define MAX 20

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

// SCAN algorithm (moving toward higher cylinders first)
int scan(int req[], int n, int head, int disk_size) {
    int total = 0, i;
    int arr[MAX];
    for (i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);

    int idx = 0;
    while (idx < n && arr[idx] < head) idx++;

    printf("\nSCAN Sequence: %d", head);

    // Move toward higher requests
    for (i = idx; i < n; i++) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    // Move to end of disk (499)
    total += abs((disk_size - 1) - head);
    head = disk_size - 1;
    printf(" -> %d", head);

    // Then reverse direction: service remaining lower requests
    for (i = idx - 1; i >= 0; i--) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (SCAN): %d", total);
    printf("\nAverage Seek Distance (SCAN): %.2f\n", (float)total / n);
    return total;
}

// LOOK algorithm (moving toward higher requests first)
int look(int req[], int n, int head) {
    int total = 0, i;
    int arr[MAX];
    for (i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);

    int idx = 0;
    while (idx < n && arr[idx] < head) idx++;

    printf("\nLOOK Sequence: %d", head);

    // Move toward higher requests
    for (i = idx; i < n; i++) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    // Reverse directly to lowest pending request
    for (i = idx - 1; i >= 0; i--) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (LOOK): %d", total);
    printf("\nAverage Seek Distance (LOOK): %.2f\n", (float)total / n);
    return total;
}

int main() {
    int disk_size = 500;
    int head = 185;
    int req[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};
    int n = sizeof(req) / sizeof(req[0]);

    printf("Disk size: 0 - %d\n", disk_size - 1);
    printf("Current Head: %d\nPending Requests: ", head);
    for (int i = 0; i < n; i++) printf("%d ", req[i]);
    printf("\n");

    int total_scan = scan(req, n, head, disk_size);
    int total_look = look(req, n, head);

    printf("\n--- COMPARISON ---\n");
    printf("SCAN Total Movement : %d\n", total_scan);
    printf("LOOK Total Movement : %d\n", total_look);

    if (total_look < total_scan)
        printf("\n✅ LOOK performed better (less total head movement).\n");
    else
        printf("\n✅ SCAN performed better (less total head movement).\n");

    return 0;
}
/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL$ cd 8
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/8$ gcc 8.2.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/8$ ./out
Disk size: 0 - 499
Current Head: 185
Pending Requests: 20 229 39 450 18 145 120 380 20 250 

SCAN Sequence: 185 -> 229 -> 250 -> 380 -> 450 -> 499 -> 145 -> 120 -> 39 -> 20 -> 20 -> 18
Total Head Movement (SCAN): 795
Average Seek Distance (SCAN): 79.50

LOOK Sequence: 185 -> 229 -> 250 -> 380 -> 450 -> 145 -> 120 -> 39 -> 20 -> 20 -> 18
Total Head Movement (LOOK): 697
Average Seek Distance (LOOK): 69.70

--- COMPARISON ---
SCAN Total Movement : 795
LOOK Total Movement : 697

✅ LOOK performed better (less total head movement).
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/8$ 
*/
