#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main()
{
    key_t key = 1234;
    int shmid;
    char *data;
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    data = (char *)shmat(shmid, NULL, 0);
    strcpy(data, "Hello from Shared Memory!");
    printf("Written: %s\n", data);
    printf("Read: %s\n", data);
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
