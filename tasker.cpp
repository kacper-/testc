//
// Created by Kacper Marczewski on 05/04/2022
//

#include<string>
#include<iostream>
#include<thread>
#include<vector>

void print(int n, const std::string &str)  {
    std::cout << n << " " << str << std::endl;
}

int main() {
    std::vector<std::string> s = {
            "Educative.blog",
            "Educative",
            "courses",
            "are great"
    };
    std::vector<std::thread> threads;

    for (int i = 0; i < s.size(); i++) {
        threads.push_back(std::thread(print, i, s[i]));
    }

    for (auto &th : threads) {
        th.join();
    }
    return 0;
}

=============================


void errno_abort(const char* header)
{
    perror(header);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
#define SERVERPORT 4567
    struct sockaddr_in send_addr, recv_addr;
    int trueflag = 1, count = 0;
    int fd;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        errno_abort("socket");
#ifndef RECV_ONLY
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST,
                   &trueflag, sizeof trueflag) < 0)
        errno_abort("setsockopt");

    memset(&send_addr, 0, sizeof send_addr);
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = (in_port_t) htons(SERVERPORT);
    // broadcasting address for unix (?)
    inet_aton("127.255.255.255", &send_addr.sin_addr);
    // send_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
#endif // ! RECV_ONLY

#ifndef SEND_ONLY
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                   &trueflag, sizeof trueflag) < 0)
        errno_abort("setsockopt");

    memset(&recv_addr, 0, sizeof recv_addr);
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = (in_port_t) htons(SERVERPORT);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(fd, (struct sockaddr*) &recv_addr, sizeof recv_addr) < 0)
        errno_abort("bind");
#endif // ! SEND_ONLY

    while ( 1 ) {
#ifndef RECV_ONLY
        char sbuf[256] = {};
        snprintf(sbuf, sizeof(sbuf), "Hello(%d)!", count++);
        if (sendto(fd, sbuf, strlen(sbuf)+1, 0,
                   (struct sockaddr*) &send_addr, sizeof send_addr) < 0)
            errno_abort("send");
        printf("send: %s\n", sbuf);
        usleep(1000000/2);
#endif // ! RECV_ONLY

#ifndef SEND_ONLY
        char rbuf[256] = {};
        if (recv(fd, rbuf, sizeof(rbuf)-1, 0) < 0)
            errno_abort("recv");
        printf("recv: %s\n", rbuf);
#endif // ! SEND_ONLY
    }
    close(fd);
    return 0;
}

