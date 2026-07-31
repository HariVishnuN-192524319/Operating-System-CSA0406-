#include <stdio.h>
int main() {
    int n, i, j, bt[10], pr[10], wt[10], tat[10], p[10], temp;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Burst Time and Priority of P%d: ", p[i]);
        scanf("%d%d", &bt[i], &pr[i]);
    }
    // Sort by Priority
    for(i = 0; i < n - 1; i++)
        for(j = i + 1; j < n; j++)
            if(pr[i] > pr[j]) {
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i];  p[i] = p[j];  p[j] = temp;
            }
    wt[0] = 0;
    for(i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    printf("\nP\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
    }
    return 0;
}
