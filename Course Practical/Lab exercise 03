int printf(const char *format, ...);
int scanf(const char *format, ...);

void calculateWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
}

void calculateTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void calculateAverageTime(int processes[], int n, int bt[]) {
    int wt[100]; 
    int tat[100];
    float total_wt = 0;
    float total_tat = 0;

    calculateWaitingTime(processes, n, bt, wt);
    calculateTurnaroundTime(processes, n, bt, wt, tat);

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (double)(total_wt / (float)n));
    printf("\nAverage Turnaround Time = %.2f\n", (double)(total_tat / (float)n));
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    int processes[100];
    int burst_time[100];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1; 
        printf("Enter burst time for Process P%d: ", processes[i]);
        scanf("%d", &burst_time[i]);
    }

    calculateAverageTime(processes, n, burst_time);

    return 0;
}
