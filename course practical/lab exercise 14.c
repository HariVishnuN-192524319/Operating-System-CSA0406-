#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_LEN 30

struct Directory {
    char dir_name[MAX_LEN];
    char file_names[MAX_FILES][MAX_LEN];
    int file_count;
};

int main() {
    struct Directory dir;
    dir.file_count = 0;
    int choice;
    char name[MAX_LEN];

    printf("Enter Directory Name: ");
    scanf("%s", dir.dir_name);

    while (1) {
        printf("\n--- Directory: %s ---\n", dir.dir_name);
        printf("1. Create File\t2. Delete File\n3. Search File\t4. Display Directory\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Create
                if (dir.file_count >= MAX_FILES) {
                    printf("Directory is full!\n");
                    break;
                }
                printf("Enter File Name: ");
                scanf("%s", name);
                
                int exists = 0;
                for (int i = 0; i < dir.file_count; i++) {
                    if (strcmp(dir.file_names[i], name) == 0) exists = 1;
                }
                if (exists) {
                    printf("File '%s' already exists!\n", name);
                } else {
                    strcpy(dir.file_names[dir.file_count++], name);
                    printf("File created.\n");
                }
                break;

            case 2: // Delete
                printf("Enter File Name to Delete: ");
                scanf("%s", name);
                int found = 0;
                for (int i = 0; i < dir.file_count; i++) {
                    if (strcmp(dir.file_names[i], name) == 0) {
                        found = 1;
                        strcpy(dir.file_names[i], dir.file_names[dir.file_count - 1]);
                        dir.file_count--;
                        printf("File deleted.\n");
                        break;
                    }
                }
                if (!found) printf("File not found!\n");
                break;

            case 3: // Search
                printf("Enter File Name to Search: ");
                scanf("%s", name);
                int is_present = 0;
                for (int i = 0; i < dir.file_count; i++) {
                    if (strcmp(dir.file_names[i], name) == 0) is_present = 1;
                }
                printf(is_present ? "File found in directory.\n" : "File not found.\n");
                break;

            case 4: // Display
                if (dir.file_count == 0) {
                    printf("Directory is empty.\n");
                } else {
                    printf("Files in '%s':\n", dir.dir_name);
                    for (int i = 0; i < dir.file_count; i++) {
                        printf(" - %s\n", dir.file_names[i]);
                    }
                }
                break;

            case 5: // Exit
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}