#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int at[10], bt[10], rt[10], pr[10];
    int wt[10], tat[10], ct[10];
    int min, p;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("AT BT Priority of P%d: ", i + 1);
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    while(completed < n) {
        min = 9999;
        p = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && pr[i] < min) {
                min = pr[i];
                p = i;
            }
        }

        if(p == -1) {
            time++;
            continue;
        }

        rt[p]--;
        time++;

        if(rt[p] == 0) {
            completed++;
            ct[p] = time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];
        }
    }

    printf("\nP\tAT\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], wt[i], tat[i]);

    return 0;
}
