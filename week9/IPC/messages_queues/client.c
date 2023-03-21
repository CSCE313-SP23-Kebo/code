#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// message queue structure
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
    message.mesg_type = 1;

    printf("Insert message  : ");
    fgets(message.mesg_text, sizeof message.mesg_text, stdin);

    // send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message
    printf("Message sent to server : %s\n", message.mesg_text);

    return 0;
}