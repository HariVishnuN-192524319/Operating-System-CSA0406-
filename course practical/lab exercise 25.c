#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd;
    char buffer[20];
    struct stat file_stat;
    DIR *dir;
    struct dirent *entry;

    if (stat("demo.txt", &file_stat) == 0) {
        printf("File Size: %ld bytes\n", file_stat.st_size);
    } else {
        printf("stat failed! Make sure 'demo.txt' exists.\n");
    }

    fd = open("demo.txt", O_RDONLY);
    if (fd >= 0) {
        printf("File opened successfully with descriptor: %d\n", fd);

        lseek(fd, 5, SEEK_SET);
        int bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            printf("Read after lseek(5): %s\n", buffer);
        }
        close(fd);
    }

    dir = opendir(".");
    if (dir) {
        printf("\nDirectory Files:\n");
        while ((entry = readdir(dir)) != NULL) {
            printf(" - %s\n", entry->d_name);
        }
        closedir(dir);
    }

    return 0;
}