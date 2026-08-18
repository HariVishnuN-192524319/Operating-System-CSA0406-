#include <stdio.h>
#include <dirent.h>
int main() {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        printf("Could not open directory.\n");
        return 1;
    }
    printf("Files and Directories:\n---------\n");
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden entries '.' and '..' for cleaner output
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
    return 0;
}