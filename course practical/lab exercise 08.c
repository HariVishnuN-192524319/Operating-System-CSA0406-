#include <stdio.h>
int main() {
    int n, i, time = 0, remain, tq;
    int bt[20], rt[20], wt[20], tat[20];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    // Input Burst Time
    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for Process P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // Remaining Time
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    remain = n;
    while(remain != 0) {
        for(i = 0; i < n; i++) {
            if(rt[i] > 0) {
                if(rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];
                    remain--;
                }
                else {
                    rt[i] -= tq;
                    time += tq;
                }
            }
        }
    }
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float avgWT = 0, avgTAT = 0;
    for(i = 0; i < n; i++) 
        printf("P%d\t%d\t\t%d\t\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
        avgWT += wt[i];
        avgTAT += tat[i];
    }
    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);
    return 0;
}
