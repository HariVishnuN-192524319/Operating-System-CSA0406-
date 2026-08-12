int printf(const char *f, ...);
int scanf(const char *f, ...);

int main() {
    int n, t, p[100], bt[100], wt[100], tat[100];
    float twt = 0, ttat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Burst time P%d: ", p[i]);
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                t = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = t;
                t = p[j]; p[j] = p[j + 1]; p[j + 1] = t;
            }
        }
    }

    wt[0] = 0;
    tat[0] = bt[0];
    ttat = tat[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
        twt += wt[i];
        ttat += tat[i];
    }

    printf("\nP\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAvg WT = %.2f", (double)(twt / n));
    printf("\nAvg TAT = %.2f\n", (double)(ttat / n));

    return 0;
}
