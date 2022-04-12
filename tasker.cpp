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
#include <mutex>

int port;
char ip[20];
std::mutex mtx;

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

std::vector<task> tasks;

std::string status(int s)
{
    switch (s)
    {
    case 0:
        return "pending";
    case 1:
        return "locked";
    case 2:
        return "in progress";
    case 3:
        return "finished";
    
    default:
        return "unknown";
    }
}

void print_vec() {
    printf("tasks:\n");
    for(auto task : tasks)
        printf("\t%s %s\n", task.name.c_str(), status(task.status).c_str());
}

void errno_abort(const char* header)
{
    perror(header);
    exit(EXIT_FAILURE);
}

void send_udp(char* name)
{
    struct sockaddr_in send_addr;
    int trueflag = 1;
    int fd;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        errno_abort("socket");
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof trueflag) < 0)
        errno_abort("setsockopt");

    memset(&send_addr, 0, sizeof send_addr);
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = (in_port_t) htons(port);
    inet_aton(ip, &send_addr.sin_addr);

    char msg[strlen(name)+3];
    strcpy(msg, "0");
    strcat(msg, name);

    if (sendto(fd, msg, strlen(msg), 0, (struct sockaddr*) &send_addr, sizeof send_addr) < 0)
        errno_abort("sendto");

    close(fd);
}

void start_task(task t)
{
    // TODO send message about starting new task, wait a while and if there is no objections start the task
}

void process_task(task t)
{
    {
        std::lock_guard<std::mutex> lck(mtx);
        if(t.status)
        {
            for(auto tt : tasks)
            {
                if(t.name == tt.name)
                    t.status = tt.status;
            }
        } else {
            tasks.push_back(t);
            start_task(t);
        }
    }
    print_vec();
}

void verify_params(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Usage: tasker broadcast_ip port\n");
        printf("submitted parameters [%d]:\n", argc);
        for(int i=0;i<argc;i++)
            printf("\t%s\n", argv[i]);
        exit(0);
    }
}

void run(int fd) {
    while ( 1 ) {
        char rbuf[256] = {};
        if (recv(fd, rbuf, sizeof(rbuf)-1, 0) < 0)
        {
            errno_abort("recv");
        }
        else
        {
            int status=rbuf[0]-48;
            std::string s(rbuf);
            task t(s.substr(1,s.length()-1));
            t.status=status;
            process_task(t);
        }
    }
}

int bind_udp()
{
    struct sockaddr_in recv_addr;
    int trueflag = 1;
    int fd;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        errno_abort("socket");

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof trueflag) < 0)
        errno_abort("setsockopt");

    memset(&recv_addr, 0, sizeof recv_addr);
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = (in_port_t) htons(port);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr*) &recv_addr, sizeof recv_addr) < 0)
        errno_abort("bind");

    return fd;
}

int main(int argc, char* argv[])
{
    verify_params(argc, argv);

    port = atoi(argv[2]);
    strcpy(ip, argv[1]);
    int fd = bind_udp();

    run(fd);

    close(fd);
    return 0;
}

