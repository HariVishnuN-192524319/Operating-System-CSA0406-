#include <stdio.h>
#include <string.h>
#define MAX_RECORDS 100
struct Record {
    int id;
    char data[30];
};
int main() {
    struct Record file[MAX_RECORDS];
    int record_count = 0, choice, search_id;
    while (1) {
        printf("\n--- Sequential File Allocation ---\n");
        printf("1. Add Record\n2. Read Record (Sequential Access)\n3. Display All Records\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 1) { // Add record sequentially
            if (record_count >= MAX_RECORDS) {
                printf("File is full!\n");
                continue;
            }
            printf("Enter Record ID: ");
            scanf("%d", &file[record_count].id);
            printf("Enter Record Data: ");
            scanf("%s", file[record_count].data);
            record_count++;
            printf("Record stored sequentially at Block %d.\n", record_count - 1);
        } 
        else if (choice == 2) { // Access record sequentially from start
            if (record_count == 0) {
                printf("File is empty!\n");
                continue;
            }
            printf("Enter Record ID to search: ");
            scanf("%d", &search_id);
            int found = 0;
            printf("\nTraversing records sequentially from Block 0:\n");
            for (int i = 0; i < record_count; i++) {
                printf(" -> Reading Block %d (ID: %d)... ", i, file[i].id);
                if (file[i].id == search_id) {
                    printf("[MATCH FOUND]\n");
                    printf("Record Details -> ID: %d, Data: %s\n", file[i].id, file[i].data);
                    printf("Total blocks accessed: %d\n", i + 1);
                    found = 1;
                    break;
                } else {
                    printf("[Passed]\n");
                }
            }
            if (!found) {
                printf("Record ID %d not found after scanning all %d records.\n", search_id, record_count);
            }
        } 
        else if (choice == 3) { // Display file structure
            if (record_count == 0) {
                printf("File is empty!\n");
            } else {
                printf("\nBlock | Record ID | Data\n");
                printf("-------------------------\n");
                for (int i = 0; i < record_count; i++) {
                    printf("  %2d  |     %2d    | %s\n", i, file[i].id, file[i].data);
                }
            }
        } 
        else if (choice == 4) {
            break;
        } 
        else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
