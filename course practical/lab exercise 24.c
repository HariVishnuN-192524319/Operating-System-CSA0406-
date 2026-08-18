#include <stdio.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <string.h>

int main() {
    char text[] = "Hello UNIX System Calls!";
    char buffer[50];
    int fd;

    fd = open("demo.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("File creation failed");
        return 1;
    }
    write(fd, text, strlen(text));
    printf("Successfully wrote to file using write()\n");
    close(fd);

    fd = open("demo.txt", O_RDONLY);
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';
    printf("Read from file: %s\n", buffer);
    lseek(fd, 6, SEEK_SET); // Skip the first 6 characters ("Hello ")
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';
    printf("Read after lseek(6): %s\n", buffer);
    close(fd);
    return 0;
}