#include <stdio.h>

int main() {
    int pages[20], frames[10];
    int n, f_count, page_faults = 0, index = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f_count);

    // Initialize frames to -1 (empty)
    for (int i = 0; i < f_count; i++) frames[i] = -1;

    printf("\nRef String | Frames | Status\n");
    printf("--------------------------------\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frames (Hit)
        for (int j = 0; j < f_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // Page Fault (Miss)
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % f_count; // FIFO replacement index
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
