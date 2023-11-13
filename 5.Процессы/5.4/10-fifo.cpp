#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define IN_FIFO "/home/box/in.fifo"
#define OUT_FIFO "/home/box/out.fifo"

int main() {
    unlink(IN_FIFO);
    unlink(OUT_FIFO);

    if (-1 == mkfifo(IN_FIFO, 0666)) {
        return -1;
    }
    if (-1 == mkfifo(OUT_FIFO, 0666)) {
        return -1;
    }

    int in = open(IN_FIFO, O_RDONLY);
    int out = open(OUT_FIFO, O_WRONLY);

    char buffer[512];
    int bytes_read = -1;

    while (bytes_read = read(in, &buffer, 512)) {
        write(out, buffer, bytes_read);
    }

    close(in);
    close(out);

    unlink(IN_FIFO);
    unlink(OUT_FIFO);

    return 0;
}

