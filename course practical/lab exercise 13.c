#include <stdio.h>
void firstFit(int blocks[], int b, int process[], int p) {
    int alloc[p], i, j;
    for (i = 0; i < p; i++) alloc[i] = -1;
    for (i = 0; i < p; i++)
        for (j = 0; j < b; j++)
            if (blocks[j] >= process[i]) {
                alloc[i] = j;
                blocks[j] -= process[i];
                break;
            }
    printf("\nFirst Fit:\n");
    for (i = 0; i < p; i++)
        printf("Process %d -> Block %d\n", i + 1,
               alloc[i] == -1 ? 0 : alloc[i] + 1);
}
void bestFit(int blocks[], int b, int process[], int p) {
    int alloc[p], i, j, best;
    for (i = 0; i < p; i++) alloc[i] = -1;
    for (i = 0; i < p; i++) {
        best = -1;
        for (j = 0; j < b; j++)
            if (blocks[j] >= process[i] &&
                (best == -1 || blocks[j] < blocks[best]))
                best = j;
        if (best != -1) {
            alloc[i] = best;
            blocks[best] -= process[i];
        }
    }
    printf("\nBest Fit:\n");
    for (i = 0; i < p; i++)
        printf("Process %d -> Block %d\n", i + 1,
               alloc[i] == -1 ? 0 : alloc[i] + 1);
}
void worstFit(int blocks[], int b, int process[], int p) {
    int alloc[p], i, j, worst;
    for (i = 0; i < p; i++) alloc[i] = -1;
    for (i = 0; i < p; i++) {
        worst = -1;
        for (j = 0; j < b; j++)
            if (blocks[j] >= process[i] &&
                (worst == -1 || blocks[j] > blocks[worst]))
                worst = j;
        if (worst != -1) {
            alloc[i] = worst;
            blocks[worst] -= process[i];
        }
    }
    printf("\nWorst Fit:\n");
    for (i = 0; i < p; i++)
        printf("Process %d -> Block %d\n", i + 1,
               alloc[i] == -1 ? 0 : alloc[i] + 1);
}
int main() {
    int b, p, i;
  
    printf("Enter number of memory blocks: ");
    scanf("%d", &b);
    int blocks[b], original[b];
    printf("Enter block sizes:\n");
    for (i = 0; i < b; i++) {
        scanf("%d", &blocks[i]);
        original[i] = blocks[i];
    }
    printf("Enter number of processes: ");
    scanf("%d", &p);
    int process[p];
    printf("Enter process sizes:\n");
    for (i = 0; i < p; i++)
        scanf("%d", &process[i]);
    firstFit(blocks, b, process, p);
    for (i = 0; i < b; i++) blocks[i] = original[i];
    bestFit(blocks, b, process, p);
    for (i = 0; i < b; i++) blocks[i] = original[i];
    worstFit(blocks, b, process, p);
    return 0;
}
