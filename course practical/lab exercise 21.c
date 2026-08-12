#include <stdio.h>
int main() {
    int b, p, i, j, w;
    printf("Enter blocks and processes: ");
    scanf("%d%d", &b, &p);
    int block[b], proc[p];
    printf("Enter block sizes: ");
    for(i = 0; i < b; i++) scanf("%d", &block[i]);
    printf("Enter process sizes: ");
    for(i = 0; i < p; i++) scanf("%d", &proc[i]);
    for(i = 0; i < p; i++) {
        w = -1;
        for(j = 0; j < b; j++)
            if(block[j] >= proc[i] &&
              (w == -1 || block[j] > block[w]))
                w = j;
        if(w != -1) {
            printf("P%d -> Block %d\n", i + 1, w + 1);
            block[w] -= proc[i];
        } else
            printf("P%d -> Not Allocated\n", i + 1);
    }
    return 0;
}
