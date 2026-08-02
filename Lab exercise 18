#include <stdio.h>

int mutex = 1, full = 0, empty = 3, x = 0;
void wait(int *s)
{
    (*s)--;
}
void signal(int *s)
{
    (*s)++;
}
void producer()
{
    wait(&empty);
    wait(&mutex);
    x++;
    printf("Producer produced item %d\n", x);
    signal(&mutex);
    signal(&full);
}
void consumer()
{
    wait(&full);
    wait(&mutex);
    printf("Consumer consumed item %d\n", x);
    x--;
    signal(&mutex);
    signal(&empty);
}
int main()
{
    producer();
    producer();
    consumer();
    consumer();
    return 0;
}
