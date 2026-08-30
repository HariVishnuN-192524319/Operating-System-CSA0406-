#include <stdio.h>
int main() {
    int pages[20], frames[10];
    int n, f_count, page_faults = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f_count);
    for (int i = 0; i < f_count; i++) frames[i] = -1;
    printf("\nRef String | Frames | Status\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int replace_index = -1;
            int farthest = i;
            for (int j = 0; j < f_count; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
            }
            if (replace_index == -1) {
                for (int j = 0; j < f_count; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                replace_index = j;
                            }
                            break;
                        }
                    }
                    if (k == n) {
                        replace_index = j;
                        break;
                    }
                }
            }
            frames[replace_index] = pages[i];
            page_faults++;
        }
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
