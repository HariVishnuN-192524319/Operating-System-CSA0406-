#include <stdio.h>
#include <stdlib.h>
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main() {
    int req[20], n, head, disk_size, dir, total_seek = 0;
    int left[20], right[20], l_count = 0, r_count = 0;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter request queue: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter total disk size (max tracks): ");
    scanf("%d", &disk_size);
    printf("Enter direction (1 for High/Right, 0 for Low/Left): ");
    scanf("%d", &dir);
    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l_count++] = req[i];
        else right[r_count++] = req[i];
    }
    if (dir == 1) right[r_count++] = disk_size - 1; 
    else left[l_count++] = 0;                       
    sort(left, l_count);
    sort(right, r_count);
    printf("\nSCAN Traversal Order:\n");
    printf("Head Position -> Serviced Track (Seek)\n");
    int current = head;
    if (dir == 1) { // Moving Right (Towards Higher Tracks)
        for (int i = 0; i < r_count; i++) {
            int seek = abs(right[i] - current);
            total_seek += seek;
            printf(" %3d -> %3d (%d)\n", current, right[i], seek);
            current = right[i];
        }
        for (int i = l_count - 1; i >= 0; i--) {
            int seek = abs(left[i] - current);
            total_seek += seek;
            printf("%3d ->%3d(%d)\n", current, left[i], seek);
            current = left[i];
        }
    } else { // Moving Left (Towards Lower Tracks)
        for (int i = l_count - 1; i >= 0; i--) {
            int seek = abs(left[i] - current);
            total_seek += seek;
            printf("%3d -> %3d (%d)\n", current, left[i], seek);
            current = left[i];
        }
        for (int i = 0; i < r_count; i++) {
            int seek = abs(right[i] - current);
            total_seek += seek;
            printf(" %3d -> %3d (%d)\n", current, right[i], seek);
            current = right[i];
        }
    }
    printf("Total Seek Operations = %d tracks\n", total_seek);
    printf("Average Seek Time    = %.2f tracks\n", (float)total_seek / n);
    return 0;
}
