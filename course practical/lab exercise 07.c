#include <stdio.h>
int main() {
    int n, i, j;
    int bt[20], wt[20], tat[20], p[20];
    float avgWT = 0, avgTAT = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    // Input Burst Time
    for(i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Enter Burst Time for Process P%d: ", p[i]);
        scanf("%d", &bt[i]);
    }
    // Sort processes based on Burst Time
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(bt[i] > bt[j]) {
                int temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    // Calculate Waiting Time
    wt[0] = 0;
    for(i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
    // Calculate Turnaround Time
    for(i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
    }
    // Display Results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n",
               p[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
