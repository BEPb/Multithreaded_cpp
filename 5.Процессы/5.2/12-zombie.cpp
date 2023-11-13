#include <unistd.h>
#include <signal.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

    pid_t child_pid = fork();

    // child
    if (child_pid == 0) {
        
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGABRT);
        sigprocmask(SIG_BLOCK, &mask, NULL);
        pause();

        return 0;
    }

    // parent
    std::ofstream outfile ("/home/box/pid_parent");
    pid_t parent_pid = getpid();
    outfile << parent_pid << std::endl;
    outfile.close();

    std::ofstream outfile_child ("/home/box/pid_child");
    outfile_child << child_pid << std::endl;
    outfile_child.close();

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGABRT);
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    waitpid(child_pid, NULL, 0);
    
    return 0;
}

