#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(std::cin),
              std::istream_iterator<std::string>(),
              std::back_inserter<std::vector<std::string>>(tokens));

    std::vector<std::vector<std::string>> commands;
    auto first = tokens.begin();
    auto last = tokens.end();

    for (auto it = first; it != last; ++it) {
        if (*it == "|") {
            commands.emplace_back(first, it);
            first = it + 1;
        }
    }

    if (first != last) {
        commands.emplace_back(first, last);
    }

    std::vector<std::vector<char*>> cmds;

    for (auto& v : commands) {
        std::vector<char*> args;
        for (auto& str : v) {
            args.push_back(const_cast<char*>(str.c_str()));
        }
        args.push_back(nullptr);
        cmds.push_back(args);
    }

    int file_descriptors[2];
    int input_fd = STDIN_FILENO;
    pid_t process_id;
    pipe(file_descriptors);

    for (size_t idx = 0; idx < cmds.size(); ++idx) {

        pipe(file_descriptors);

        process_id = fork();

        if (process_id == -1) {
            exit(EXIT_FAILURE);
        } else if (process_id == 0) { //child

            if (idx != 0) {
                close(STDIN_FILENO);
                dup2(input_fd, STDIN_FILENO);
            }

            if (idx != commands.size() - 1) {
                close(STDOUT_FILENO);
                dup2(file_descriptors[1], STDOUT_FILENO);
            } else {
                int out = open("/home/box/result.out", O_RDWR | O_CREAT, 0666);
                dup2(out, STDOUT_FILENO);
            }

            std::vector<char*> args = cmds[idx];
            execvp(args[0], &args[0]);

            close(input_fd);

            exit(EXIT_SUCCESS);
        } else { //parent
            wait(NULL); //wait child
            close(file_descriptors[1]); //close in
            input_fd = file_descriptors[0];
        }
    }
    
    return 0;
}

