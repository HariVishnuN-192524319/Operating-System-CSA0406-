#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_BLOCKS 50
struct Block {
    int block_num;
    int next_block; // Pointer to next block (-1 if end of file)
};
int main() {
    int memory[MAX_BLOCKS] = {0}; // 0 = Free, 1 = Allocated
    struct Block disk[MAX_BLOCKS];
    int start_block, end_block, n, choice;
    // Initialize disk block pointers
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i].block_num = i;
        disk[i].next_block = -1;
    }
    while (1) {
        printf("\n--- Linked File Allocation Simulation ---\n");
        printf("1. Allocate File\n2. Display Disk Status\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter starting block number: ");
            scanf("%d", &start_block);
            printf("Enter number of blocks required: ");
            scanf("%d", &n);
            if (start_block < 0 || start_block >= MAX_BLOCKS) {
                printf("Invalid starting block!\n");
                continue;
            }
            if (memory[start_block] == 1) {
                printf("Starting block %d is already allocated!\n", start_block);
                continue;
            }
            int current = start_block;
            int allocated_count = 1;
            memory[current] = 1;
            printf("Enter remaining %d block numbers:\n", n - 1);
            for (int i = 1; i < n; i++) {
                int next;
                scanf("%d", &next);

                if (next >= 0 && next < MAX_BLOCKS && memory[next] == 0) {
                    memory[next] = 1;
                    disk[current].next_block = next;
                    current = next;
                    allocated_count++;
                } else {
                    printf("Block %d is invalid or already allocated! Skipping...\n", next);
                }
            }
            end_block = current;
            disk[end_block].next_block = -1; // End of file chain

            printf("\n--- Directory Entry ---\n");
            printf("Start Block: %d | End Block: %d | Allocated Count: %d\n", start_block, end_block, allocated_count);

            printf("\nFile Block Chain:\n");
            int ptr = start_block;
            while (ptr != -1) {
                printf("Block [%d] -> ", ptr);
                ptr = disk[ptr].next_block;
            }
            printf("NULL\n");
        } 
        else if (choice == 2) {
            printf("\nDisk Block Status (0: Free, 1: Allocated):\n");
            for (int i = 0; i < MAX_BLOCKS; i++) {
                printf("%d:%d  ", i, memory[i]);
                if ((i + 1) % 10 == 0) printf("\n");
            }
        } 
        else if (choice == 3) {
            break;
        } 
        else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
