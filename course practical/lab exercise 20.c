#include <stdio.h>
int mutex = 1;
int readCount = 0;
void wait(int *s)
{
    (*s)--;
}
void signal(int *s)
{
    (*s)++;
}
void reader()
{
    wait(&mutex);
    readCount++;
    printf("Reader %d is reading\n", readCount);
    signal(&mutex);
    wait(&mutex);
    readCount--;
    signal(&mutex);
}
void writer()
{
    wait(&mutex);
    printf("Writer is writing\n");
    signal(&mutex);
}
int main()
{
    reader();
    reader();
    writer();
    return 0;
}
