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

// C-SCAN including mid-jump
int cscan(int req[], int n, int head, int disk_size) {
    int total = 0;
    int arr[MAX];
    for (int i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);

    int i, idx = 0;
    while (idx < n && arr[idx] < head) idx++;

    printf("\nC-SCAN Sequence: %d", head);

    // Move upwards
    for (i = idx; i < n; i++) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    // Move to end
    total += abs((disk_size - 1) - head);
    head = disk_size - 1;
    printf(" -> %d", head);

    // Jump to start (counted)
    total += abs(head - 0);
    head = 0;
    printf(" -> %d (wrap)", head);

    // Serve remaining
    for (i = 0; i < idx; i++) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (C-SCAN, jump counted): %d", total);
    printf("\nAverage Seek (C-SCAN): %.2f\n", (float)total / n);
    return total;
}

// C-LOOK including mid-jump
int clook(int req[], int n, int head) {
    int total = 0;
    int arr[MAX];
    for (int i = 0; i < n; i++) arr[i] = req[i];
    sort(arr, n);

    int i, idx = 0;
    while (idx < n && arr[idx] < head) idx++;

    printf("\nC-LOOK Sequence: %d", head);

    // Move upward
    for (i = idx; i < n; i++) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    // Jump to first (counted)
    total += abs(head - arr[0]);
    head = arr[0];
    printf(" -> %d (wrap)", head);

    // Serve remaining
    for (i = 0; i < idx; i++) {
        total += abs(arr[i] - head);
        head = arr[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (C-LOOK, jump counted): %d", total);
    printf("\nAverage Seek (C-LOOK): %.2f\n", (float)total / n);
    return total;
}

int main() {
    int disk_size = 500;
    int head = 85;
    int req[] = {10, 229, 39, 400, 18, 145, 120, 480, 20, 250};
    int n = sizeof(req) / sizeof(req[0]);

    printf("Disk size: 0 - %d\n", disk_size - 1);
    printf("Current Head: %d\nPending Requests: ", head);
    for (int i = 0; i < n; i++) printf("%d ", req[i]);
    printf("\n");

    int cscan_total = cscan(req, n, head, disk_size);
    int clook_total = clook(req, n, head);

    printf("\n--- COMPARISON (Jump Counted) ---\n");
    printf("C-SCAN Total: %d\nC-LOOK Total: %d\n", cscan_total, clook_total);

    if (clook_total < cscan_total)
        printf("\n✅ C-LOOK performed better.\n");
    else
        printf("\n✅ C-SCAN performed better.\n");

    return 0;
}

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/8$ gcc 8.1.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/8$ ./out
Disk size: 0 - 499
Current Head: 85
Pending Requests: 10 229 39 400 18 145 120 480 20 250 

C-SCAN Sequence: 85 -> 120 -> 145 -> 229 -> 250 -> 400 -> 480 -> 499 -> 0 (wrap) -> 10 -> 18 -> 20 -> 39
Total Head Movement (C-SCAN, jump counted): 952
Average Seek (C-SCAN): 95.20

C-LOOK Sequence: 85 -> 120 -> 145 -> 229 -> 250 -> 400 -> 480 -> 10 (wrap) -> 10 -> 18 -> 20 -> 39
Total Head Movement (C-LOOK, jump counted): 894
Average Seek (C-LOOK): 89.40

--- COMPARISON (Jump Counted) ---
C-SCAN Total: 952
C-LOOK Total: 894

✅ C-LOOK performed better.
*/
