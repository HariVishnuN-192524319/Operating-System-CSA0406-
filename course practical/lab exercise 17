#include <stdio.h>
int main()
{
    int p, r, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0}, safe[10];
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);
    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < p; i++)
        for(j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    printf("Enter Maximum Matrix:\n");
    for(i = 0; i < p; i++)
        for(j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    printf("Enter Available Resources:\n");
    for(i = 0; i < r; i++)
        scanf("%d", &avail[i]);
    // Calculate Need Matrix
    for(i = 0; i < p; i++)
        for(j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    int count = 0;
    while(count < p)
    {
        for(i = 0; i < p; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < r; j++)
                {
                    if(need[i][j] > avail[j])
                        break;
                }
                if(j == r)
                {
                    printf("P%d executed\n", i);
                    for(k = 0; k < r; k++)
                        avail[k] += alloc[i][k];
                    safe[count++] = i;
                    finish[i] = 1;
                }
            }
        }
    }
    printf("\nSafe Sequence: ");
    for(i = 0; i < p; i++)
        printf("P%d ", safe[i]);
    return 0;
}
