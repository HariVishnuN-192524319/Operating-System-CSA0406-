#include <stdio.h>
#include <pthread.h>
void *threadFunc(void *arg)
{
    printf("Thread is running\n");
    return NULL;
}
int main()
{
    pthread_t t;
    pthread_create(&t, NULL, threadFunc, NULL);
    pthread_join(t, NULL);
    printf("Main thread completed\n");
    return 0;
}
