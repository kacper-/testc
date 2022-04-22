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
#include <random>
#include<thread>

int port;
char ip[20];
std::mutex mtx;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> bid_int(0, 50000);

class task
{
public:
    std::string name;
    int status;
    int local_bid;
    int remote_bid;
    task(std::string);
};

task::task(std::string n)
{
    name=n;
    status=0;
    local_bid=0;
    remote_bid=0;
}

std::vector<task> tasks;

std::string status(int s)
{
    switch (s)
    {
    case 0:
        return "pending"; // newly received task
    case 1:
        return "bid";   // under bid
    case 2:
        return "in progress"; // if another instance is processing it
    case 3:
        return "running";  // if this instance is processing it    
    case 4:
        return "finished"; // finished
    
    default:
        return "unknown";
    }
}

void print_vec() {
    printf("tasks:\n");
    for(auto task : tasks)
        printf("\t%s \t%s \t%d \t%d\n", task.name.c_str(), status(task.status).c_str(), task.local_bid, task.remote_bid);
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

void start_task(task *t)
{
    {
        std::lock_guard<std::mutex> lck(mtx);
        t->status = 1;
        t->local_bid = bid_int(mt);
    }
    // send bid
    // wait for 2 seconds
    // if bid is won then start the task and set status to 'running', currently running task means just waitnig for 10 seconds and then setting status 'finished'
    // if bid is lost set status to 'in progress'
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
                    if(t.status==1)
                        tt.remote_bid=t.remote_bid;
                    tt.status = t.status;
            }
        } else {
            tasks.push_back(t);
            std::thread(start_task, &t);
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
            if(status == 1) 
            {
                t.name=s.substr(9,s.length()-9);            
                t.remote_bid=atoi(s.substr(1,8).c_str());
            }
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

