#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main() {
    sem_t* sem = sem_open("/test.sem", O_CREAT, 0666, 66);

    return 0;
}
