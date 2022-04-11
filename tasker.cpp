//
// Created by Kacper Marczewski on 05/04/2022
//

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

class task
{
public:
    std::string name;
    int status;
    task(std::string);
};

task::task(std::string n)
{
    name=n;
    status=0;
}

std::string status(int s)
{
    switch (s)
    {
    case 0:
        return "pending";
    case 1:
        return "in progress";
    case 2:
        return "finished";
    
    default:
        return "unknown";
    }
}

void print_vec(std::vector<task> tasks) {
    printf("tasks:\n");
    for(auto task : tasks)
        printf("%s %s\n", task.name.c_str(), status(task.status).c_str());
}

void errno_abort(const char* header)
{
    perror(header);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    struct sockaddr_in recv_addr;
    int trueflag = 1;
    int fd;
    std::vector<task> tasks;

    if(argc != 2) {
        printf("Usage: tasker port\n");
        printf("submitted parameters [%d]:\n", argc);
        for(int i=0;i<argc;i++)
            printf("\t%s\n", argv[i]);
        return 0;
    }

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        errno_abort("socket");

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof trueflag) < 0)
        errno_abort("setsockopt");

    memset(&recv_addr, 0, sizeof recv_addr);
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = (in_port_t) htons(atoi(argv[1]));
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr*) &recv_addr, sizeof recv_addr) < 0)
        errno_abort("bind");

    while ( 1 ) {
        char rbuf[256] = {};
        if (recv(fd, rbuf, sizeof(rbuf)-1, 0) < 0)
        {
            errno_abort("recv");
        }
        else
        {
            tasks.push_back(task(rbuf));
            print_vec(tasks);
        }
    }
    close(fd);
    return 0;
}

