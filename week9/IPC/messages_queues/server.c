#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;

    // generate unique key
    key = ftok("somefile", 65);

    // create a message queue and return identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Waiting for a message from client...\n");

    // receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    // display the message
    printf("Message received from client : %s\n", message.mesg_text);

    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
