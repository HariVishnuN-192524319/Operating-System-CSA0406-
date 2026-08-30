#include <stdio.h>
#include <stdlib.h>
#define MAX_BLOCKS 50
int main() {
    int memory[MAX_BLOCKS] = {0}; // 0 = Free, 1 = Allocated
    int index_block, n, blocks[MAX_BLOCKS];
    char choice;
    do {
        printf("\nEnter Index Block number: ");
        scanf("%d", &index_block);
        if (index_block < 0 || index_block >= MAX_BLOCKS) {
            printf("Invalid Index Block number!\n");
            continue;
        }
        if (memory[index_block] != 0) {
            printf("Index Block %d is already allocated!\n", index_block);
            continue;
        }
        printf("Enter number of blocks required for file: ");
        scanf("%d", &n);
        printf("Enter the block numbers for the file:\n");
        int count = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &blocks[i]);
            if (memory[blocks[i]] == 0) {
                count++;
            }
        }
        if (count == n) {
            // Allocate index block and file blocks
            memory[index_block] = 1;
            for (int i = 0; i < n; i++) {
                memory[blocks[i]] = 1;
            }
            printf("\n--- File Allocated Successfully ---\n");
            printf("Index Block: %d\n", index_block);
            printf("Indexed Pointers:\n");
            for (int i = 0; i < n; i++) {
                printf("  Index [%d] -> Block %d\n", i, blocks[i]);
           }
        } else {
            printf("\nFile Allocation Failed! One or more blocks are already allocated.\n");
        }
        printf("\nDo you want to enter another file? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
    return 0;
}
