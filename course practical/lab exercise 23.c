#include <stdio.h>
int main() {
    int b, p, i, j, found;
    printf("Enter blocks and processes: ");
    scanf("%d%d", &b, &p);
    int block[b], proc[p];
    printf("Enter block sizes: ");
    for(i=0;i<b;i++) scanf("%d",&block[i]);
    printf("Enter process sizes: ");
    for(i=0;i<p;i++) scanf("%d",&proc[i]);
    for(i=0;i<p;i++) {
        found = 0;
        for(j=0;j<b;j++) {
            if(block[j] >= proc[i]) {
                printf("P%d -> Block %d\n", i+1, j+1);
                block[j] -= proc[i];
                found = 1;
                break;
            }
        }
        if(!found)
            printf("P%d -> Not Allocated\n", i+1);
    }
    return 0;
}
