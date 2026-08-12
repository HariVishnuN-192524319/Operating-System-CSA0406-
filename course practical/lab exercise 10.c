#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct message {
    long type;
    char text[100];
};
int main() {
    key_t key = 1234;
    int msgid;
    struct message msg;
    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    // Sender
    msg.type = 1;
    printf("Enter message: ");
    fgets(msg.text, sizeof(msg.text), stdin);
    msgsnd(msgid, &msg, sizeof(msg.text), 0);
    // Receiver
    msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);
    printf("Received Message: %s", msg.text);
    // Delete queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
