#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGES 20     // Number of pages in reference string
#define MAX_PAGE_NUM 10  // Page numbers range from 0 to 9

// Function to generate random page reference string
void generatePageReference(int pages[], int n) {
    for (int i = 0; i < n; i++) {
        pages[i] = rand() % MAX_PAGE_NUM;
    }
}

// FIFO page replacement algorithm
int fifo(int pages[], int n, int frameCount) {
    int frames[7]; // max frames = 7
    int pageFaults = 0;
    int nextToReplace = 0;

    // Initialize frames
    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page already present
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If not found → page fault
        if (!found) {
            frames[nextToReplace] = pages[i];
            nextToReplace = (nextToReplace + 1) % frameCount;
            pageFaults++;
        }
    }

    return pageFaults;
}

// LRU page replacement algorithm
int lru(int pages[], int n, int frameCount) {
    int frames[7]; // max frames = 7
    int time[7];   // stores last used time for each frame
    int pageFaults = 0;
    int counter = 0;

    // Initialize frames and times
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        time[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = counter++; // update last used time
                break;
            }
        }

        // If not found → page fault occurs
        if (!found) {
            int lruIndex = 0;

            // Find empty frame first
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    lruIndex = j;
                    break;
                }
                // Find least recently used
                if (time[j] < time[lruIndex]) {
                    lruIndex = j;
                }
            }

            frames[lruIndex] = pages[i];
            time[lruIndex] = counter++;
            pageFaults++;
        }
    }

    return pageFaults;
}

int main() {
    int pages[MAX_PAGES];
    srand(time(0));

    // Generate random page-reference string
    generatePageReference(pages, MAX_PAGES);

    printf("=== PAGE REPLACEMENT ALGORITHMS ===\n");
    printf("Page Reference String: ");
    for (int i = 0; i < MAX_PAGES; i++)
        printf("%d ", pages[i]);
    printf("\n\n");

    printf("Frames | FIFO Faults | LRU Faults\n");
    printf("----------------------------------\n");

    for (int frameCount = 1; frameCount <= 7; frameCount++) {
        int fifoFaults = fifo(pages, MAX_PAGES, frameCount);
        int lruFaults = lru(pages, MAX_PAGES, frameCount);
        printf("  %d\t|\t%2d\t|\t%2d\n", frameCount, fifoFaults, lruFaults);
    }

    return 0;
}

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/6$ gcc 6.1.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/6$ ./out
=== PAGE REPLACEMENT ALGORITHMS ===
Page Reference String: 1 1 5 3 0 9 5 8 2 4 9 0 1 9 6 4 3 5 5 1 

Frames | FIFO Faults | LRU Faults
----------------------------------
  1	|	18	|	18
  2	|	18	|	18
  3	|	17	|	17
  4	|	16	|	16
  5	|	12	|	14
  6	|	12	|	12
  7	|	12	|	12
*/
