#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <fstream>

pthread_mutex_t mutex;
pthread_cond_t cond_var;
pthread_barrier_t barrier;

static void* thread_start(void* arg) {
    std::cout << "worker thread is waiting mutex..." << std::endl;
    
    pthread_mutex_lock(&mutex);
    std::cout << "worker thread has got mutex" << std::endl;

    sleep(5);
    std::cout << "worker thread is signaling..." << std::endl;

    pthread_cond_signal(&cond_var);
    std::cout << "worker thread is unlocking mutex..." << std::endl;

    sleep(5);

    pthread_mutex_unlock(&mutex);
    std::cout << "worker thread is waiting barrier..." << std::endl;

    pthread_barrier_wait(&barrier);
    std::cout << "worker thread has got barrier" << std::endl;

    return NULL;
}

int main() {
    pid_t pid = getpid();

    std::ofstream ofile("/home/box/main.pid");
    ofile << pid;
    ofile.close();

    pthread_t thread_id;
    pthread_attr_t thread_attr;
    pthread_barrier_init(&barrier, NULL, 2);

    pthread_attr_init(&thread_attr);
    pthread_mutex_lock(&mutex);
    
    std::cout << "main thread has locked mutex" << std::endl;

    sleep(5);

    pthread_create(&thread_id, &thread_attr, thread_start, NULL);

    std::cout << "main thread has created another thread" << std::endl;
    std::cout << "main thread is waiting cond var..." << std::endl;

    pthread_cond_wait(&cond_var, &mutex);

    std::cout << "main thread has got cond var" << std::endl;

    pthread_mutex_unlock(&mutex);

    std::cout << "main thread is waiting barrier..." << std::endl;
    pthread_barrier_wait(&barrier);
    std::cout << "main thread has got barrier" << std::endl;

    pthread_join(thread_id, NULL);

    return 0;
}

