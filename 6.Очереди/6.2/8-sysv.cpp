#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MSG_LEN 80

struct message {
    long mtype;
    char mtext[MSG_LEN] = { 0 };
};

int main() {
    key_t key = ftok("/tmp/msg.temp", 1);
    int msgid = msgget(key, IPC_CREAT | 0666);

    message msg;
    memset(&msg, 0, sizeof(message));
    ssize_t actual = msgrcv(msgid, &msg, MSG_LEN, 0, 0);

    FILE* out = fopen("/home/box/message.txt", "w+");
    fwrite(&(msg.mtext), MSG_LEN, 1, out);
    fclose(out);

    /*
     * Compiled, ran and pressed the "Send" button.
     * Then, deleted all the characters in the message.txt and hit "Send" once more.
     */

    return 0;
}

