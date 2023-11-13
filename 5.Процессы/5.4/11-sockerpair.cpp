#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int socks[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socks)) {
        return -1;
    }

    pid = fork();

    if (pid == -1) {
        return -1;
    }

    if (pid == 0) {
        close(socks[0]);
        while (true) {}
    } else {
        close(socks[1]);
        while (true) {}
    }

    return 0;
}

