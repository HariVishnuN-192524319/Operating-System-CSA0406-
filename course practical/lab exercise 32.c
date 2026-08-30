#include <stdio.h>

int main() {
    int pages[20], frames[10], time[10];
    int n, f_count, page_faults = 0, counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f_count);

    // Initialize frames and timestamps
    for (int i = 0; i < f_count; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nRef String | Frames | Status\n");
    printf("--------------------------------\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        counter++; // Increment logical timestamp

        // Check for Page Hit
        for (int j = 0; j < f_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = counter; // Update last used timestamp
                break;
            }
        }

        // Page Fault (Miss)
        if (!found) {
            int lru_index = 0;

            // Find an empty frame or the least recently used frame
            for (int j = 0; j < f_count; j++) {
                if (frames[j] == -1) {
                    lru_index = j;
                    break;
                }
                if (time[j] < time[lru_index]) {
                    lru_index = j;
                }
            }

            frames[lru_index] = pages[i];
            time[lru_index] = counter;
            page_faults++;
        }

        // Display status
        printf("    %2d     | ", pages[i]);
        for (int j = 0; j < f_count; j++) {
            if (frames[j] != -1) printf("%2d ", frames[j]);
            else printf(" - ");
        }
        printf("| %s\n", found ? "HIT" : "FAULT");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);
    return 0;
}
