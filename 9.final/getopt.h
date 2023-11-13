#include <getopt.h>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#pragma once

struct globalArgs_t {
    uint16_t port;           /* param -p */
    const char *host;        /* param -h */
    const char *dir_name;    /* param -d */
} globalArgs;

static const char *optString = "h:p:d:?";

void display_usage(const char *prg_name) {
    puts("stepik final task simple epoll http-server");
    printf("%s -h <ip> -p <port> -d <directory>/n", prg_name);
    exit(EXIT_FAILURE);
}

void get_command_line(const int &argc, char **argv, sockaddr_in &s_in, std::string& serv_dir) {
    int opt = 0;
    globalArgs.port = 0;
    globalArgs.host = nullptr;
    globalArgs.dir_name = nullptr;
    opt = getopt(argc, argv, optString);

    while (opt != -1) {
        switch (opt) {
            case ('h'):
                globalArgs.host = optarg;
                break;
            case ('d'):
                globalArgs.dir_name = optarg;
                break;
            case ('p'):
                globalArgs.port = atoi(optarg);
                break;
            case '?':
                display_usage(argv[0]);
                break;
            default:
                break;
        }
        opt = getopt(argc, argv, optString);
    }

    if(argc<4) {display_usage(argv[0]);exit(1);}
    s_in.sin_addr.s_addr = inet_addr(globalArgs.host);
    s_in.sin_port = htons(globalArgs.port);
    serv_dir =  globalArgs.dir_name;

}

