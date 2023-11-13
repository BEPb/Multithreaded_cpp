#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <iostream>

#define SHM_SIZE 1024 * 1024

int main() {
    key_t key;
    if ((key = ftok("/tmp/mem.temp", 1)) == -1) {
        std::cout << "ftok failed: " << errno << std::endl;
        return -1;
    }

    int shm_id;
    if ((shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        std::cout << "shmget failed: " << errno << std::endl;
        return -1;
    }

    char* data;
    data = (char*)shmat(shm_id, NULL, 0);
    if (data == (char*)(-1)) {
        std::cout << "shmat failed: " << errno << std::endl;
        return -1;      
    }

    for (int i = 0; i < SHM_SIZE; ++i) {
        data[i] = (char)42;
    }

    return 0;
}

