#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }
    char *pattern = argv[1];
    char *filename = argv[2];
    char line[256];
    int line_num = 1;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return 1;
    }
    printf("Matching lines in '%s' for pattern '%s':\n\n", filename, pattern);
    // Read file line by line
    while (fgets(line, sizeof(line), fp)) {
        // Search for sub-string match
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", line_num, line);
        }
        line_num++;
    }
    fclose(fp);
    return 0;
}