#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    size_t size = 1024 * 1024;
    
    int fd = shm_open("/test.shm", O_CREAT | O_RDWR, 0666);
    
    ftruncate(fd, size);

    char* addr = (char*) mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    for (size_t i = 0; i < size; ++i) {
        addr[i] = (char)13;
    }

    sleep(60);

    munmap(addr, size);

    shm_unlink("/test.shm");

    /**
     * Send the task fast!
     */

    return 0;
}

