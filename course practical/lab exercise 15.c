#include <stdio.h>
#include <string.h>

#define MAX 10

struct User {
    char name[30];
    char files[MAX][30];
    int file_count;
} users[MAX];

int user_count = 0;

int main() {
    int choice;
    char uname[30], fname[30];

    while (1) {
        printf("\n1. Add User  2. Add File  3. Search File  4. Display  5. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) { // Add User
            printf("Enter User Name: ");
            scanf("%s", users[user_count].name);
            users[user_count++].file_count = 0;
            printf("User added.\n");
        } 
        else if (choice == 2) { // Add File
            printf("Enter User Name: ");
            scanf("%s", uname);
            int u_idx = -1;
            for (int i = 0; i < user_count; i++)
                if (strcmp(users[i].name, uname) == 0) u_idx = i;

            if (u_idx == -1) {
                printf("User not found!\n");
                continue;
            }
            printf("Enter File Name: ");
            scanf("%s", fname);
            strcpy(users[u_idx].files[users[u_idx].file_count++], fname);
            printf("File added.\n");
        } 
        else if (choice == 3) { // Search File
            printf("Enter User Name: ");
            scanf("%s", uname);
            printf("Enter File Name: ");
            scanf("%s", fname);
            int found = 0;
            for (int i = 0; i < user_count; i++) {
                if (strcmp(users[i].name, uname) == 0) {
                    for (int j = 0; j < users[i].file_count; j++) {
                        if (strcmp(users[i].files[j], fname) == 0) found = 1;
                    }
                }
            }
            printf(found ? "File found!\n" : "File not found!\n");
        } 
        else if (choice == 4) { // Display
            for (int i = 0; i < user_count; i++) {
                printf("\nUser: %s\n", users[i].name);
                for (int j = 0; j < users[i].file_count; j++) {
                    printf("  - %s\n", users[i].files[j]);
                }
            }
        } 
        else if (choice == 5) break;
    }
    return 0;
}