#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int choice;
    char filename[50], buffer[200];

    while (1) {
        printf("\n--- File Management Operations ---\n");
        printf("1. Create/Write File\n2. Read File\n3. Append File\n4. Delete File\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from buffer

        if (choice == 5) break;

        printf("Enter file name: ");
        scanf("%s", filename);
        getchar(); // Clear newline character

        switch (choice) {
            case 1: // Create and Write
                fp = fopen(filename, "w");
                if (!fp) { printf("Error opening file!\n"); break; }
                printf("Enter text to write: ");
                fgets(buffer, sizeof(buffer), stdin);
                fputs(buffer, fp);
                fclose(fp);
                printf("File created and written successfully.\n");
                break;

            case 2: // Read
                fp = fopen(filename, "r");
                if (!fp) { printf("File not found!\n"); break; }
                printf("\n--- File Contents ---\n");
                while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                    printf("%s", buffer);
                }
                fclose(fp);
                break;

            case 3: // Append
                fp = fopen(filename, "a");
                if (!fp) { printf("Error opening file!\n"); break; }
                printf("Enter text to append: ");
                fgets(buffer, sizeof(buffer), stdin);
                fputs(buffer, fp);
                fclose(fp);
                printf("Content appended successfully.\n");
                break;

            case 4: // Delete
                if (remove(filename) == 0) {
                    printf("File deleted successfully.\n");
                } else {
                    printf("Unable to delete the file.\n");
                }
                break;

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}