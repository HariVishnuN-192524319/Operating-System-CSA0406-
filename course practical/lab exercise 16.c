#include <stdio.h>

struct Employee {
    int id;
    char name[20];
    float salary;
};

int main() {
    FILE *fp = fopen("emp.dat", "rb+");
    if (!fp) fp = fopen("emp.dat", "wb+");

    int choice, id;
    struct Employee e;

    while (1) {
        printf("\n1.Add  2.Display  3.Search  4.Update  5.Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) { // Add
            printf("Enter ID, Name, Salary: ");
            scanf("%d %s %f", &e.id, e.name, &e.salary);
            fseek(fp, (e.id - 1) * sizeof(struct Employee), SEEK_SET);
            fwrite(&e, sizeof(struct Employee), 1, fp);
        } 
        else if (choice == 2) { // Display All
            rewind(fp);
            while (fread(&e, sizeof(struct Employee), 1, fp))
                if (e.id > 0) printf("ID: %d | Name: %s | Salary: %.2f\n", e.id, e.name, e.salary);
        } 
        else if (choice == 3 || choice == 4) { // Search (3) or Update (4)
            printf("Enter ID: ");
            scanf("%d", &id);
            fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);

            if (fread(&e, sizeof(struct Employee), 1, fp) && e.id == id) {
                if (choice == 3) {
                    printf("Found: %s, Salary: %.2f\n", e.name, e.salary);
                } else {
                    printf("Enter new salary: ");
                    scanf("%f", &e.salary);
                    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&e, sizeof(struct Employee), 1, fp);
                    printf("Updated!\n");
                }
            } else printf("Not found!\n");
        } 
        else if (choice == 5) break;
    }
    fclose(fp);
    return 0;
}