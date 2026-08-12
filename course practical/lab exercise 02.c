#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int source, destination;
    char ch;
    source = open("source.txt", O_RDONLY);
    destination = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (read(source, &ch, 1) > 0)
    {
        write(destination, &ch, 1);
    }
    close(source);
    close(destination);
    printf("File copied successfully.\n");
    return 0;
}
