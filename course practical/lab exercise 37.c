#include <stdio.h>
#include <stdlib.h>
int main() {
    int req[20], n, head, total_seek = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("\nFCFS Disk Scheduling Traversal:\n");
    printf("Head Position -> Serviced Track (Seek Distance)\n");
    for (int i = 0; i < n; i++) {
        int seek = abs(req[i] - head);
        total_seek += seek;
        printf("    %3d       ->       %3d       (%d)\n", head, req[i], seek);
        head = req[i]; // Move head to current request
    }
    printf("Total Seek Operations = %d tracks\n", total_seek);
    printf("Average Seek Time    = %.2f tracks\n", (float)total_seek / n);

    return 0;
}
