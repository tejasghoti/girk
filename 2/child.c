#include <stdio.h>
#include <stdlib.h>

// Binary search function
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    // argc includes program name + array elements + key
    if (argc < 3) {
        printf("Insufficient arguments!\n");
        return 1;
    }

    int n = argc - 2; // last argument is key
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int key = atoi(argv[argc - 1]);

    printf("\nChild Program (Binary Search):\n");
    printf("Received Sorted Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nElement to Search: %d\n", key);

    int pos = binarySearch(arr, n, key);
    if (pos != -1)
        printf("Element %d found at position %d\n", key, pos + 1);
    else
        printf("Element %d not found in array\n", key);

    return 0;
}

