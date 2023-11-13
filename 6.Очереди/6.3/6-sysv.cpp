#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#include <iostream>

#define SEMS_CNT 16

int main() {
    key_t key = ftok("/tmp/sem.temp", 1);
    int sem_id = semget(key, SEMS_CNT, IPC_CREAT | 0666);

    if (sem_id == -1) {
        std::cout << "failed semget: " << errno << std::endl;
        return -1;
    }

    sembuf buffers[SEMS_CNT];

    for (int idx = 0; idx < SEMS_CNT; ++idx) {
        buffers[idx].sem_num = idx;
        buffers[idx].sem_flg = 0;
        buffers[idx].sem_op = idx;
    }

    if (semop(sem_id, buffers, SEMS_CNT) == -1) {
        std::cout << "failed semop: " << errno <<std::endl;
        return -1;
    }

    return 0;
}

