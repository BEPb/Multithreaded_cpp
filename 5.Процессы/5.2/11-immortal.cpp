#include <unistd.h>
#include <signal.h>
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {

    std::ofstream outfile ("/home/box/pid");
    pid_t pid = getpid();
    outfile << pid << std::endl;
    outfile.close();

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    while (true) {
        sleep(5);
    }
    
    return 0;
}

