#include <stdio.h>

// ---------- OPTIMAL PAGE REPLACEMENT ----------
int findOptimal(int pages[], int frame[], int n, int index, int frames) {
    int farthest = index, pos = -1;
    
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) // Page not found again
            return i;
    }
    
    if (pos == -1)
        return 0;
    return pos;
}

int simulateOptimal(int pages[], int n, int frames) {
    int frame[frames];
    int faults = 0;
    
    for (int i = 0; i < frames; i++)
        frame[i] = -1;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = findOptimal(pages, frame, n, i + 1, frames);
            frame[pos] = pages[i];
            faults++;
        }
    }
    return faults;
}


// ---------- LRU PAGE REPLACEMENT ----------
int findLRU(int lastUsed[], int frames) {
    int pos = 0;
    for (int i = 1; i < frames; i++)
        if (lastUsed[i] < lastUsed[pos])
            pos = i;
    return pos;
}

int simulateLRU(int pages[], int n, int frames) {
    int frame[frames], lastUsed[frames];
    int faults = 0, time = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = -1;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = j;
                lastUsed[j] = time++;
            }
        }

        if (found == -1) {
            int pos = findLRU(lastUsed, frames);
            frame[pos] = pages[i];
            lastUsed[pos] = time++;
            faults++;
        }
    }
    return faults;
}


// ---------- MAIN FUNCTION ----------
int main() {
    int pages[] = {1,2,3,4,1,2,5,1,1,2,3,4,5};
    int n = 13;
    int frames[] = {3, 4};

    printf("Page Reference String:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", pages[i]);
    printf("\n\nFrames\tOptimal Faults\tLRU Faults\n");
    printf("---------------------------------------\n");

    for (int i = 0; i < 2; i++) {
        int f = frames[i];
        int optFaults = simulateOptimal(pages, n, f);
        int lruFaults = simulateLRU(pages, n, f);
        printf("%d\t%d\t\t%d\n", f, optFaults, lruFaults);
    }

    return 0;
}

/*shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/6$ gcc 6.2.c -o out
shri@shri-ASUS-TUF-Gaming-A15-FA507RE-FA507RE:~/OSL/6$ ./out
Page Reference String:
1 2 3 4 1 2 5 1 1 2 3 4 5 

Frames	Optimal Faults	LRU Faults
---------------------------------------
3	7		10
4	6		8
*/
