//
// Created by Kacper Marczewski on 06/04/2022
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

void errno_abort(const char* header)
{
    perror(header);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    struct sockaddr_in send_addr, recv_addr;
    int trueflag = 1, count = 0;
    int fd;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        errno_abort("socket");
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST,
                   &trueflag, sizeof trueflag) < 0)
        errno_abort("setsockopt");

    memset(&send_addr, 0, sizeof send_addr);
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = (in_port_t) htons(4455);
    // broadcasting address for unix (?)
    inet_aton("192.168.1.255", &send_addr.sin_addr);
        char sbuf[256] = {};
        snprintf(sbuf, sizeof(sbuf), "Hello(%d)!", count++);
        if (sendto(fd, sbuf, strlen(sbuf)+1, 0,
                   (struct sockaddr*) &send_addr, sizeof send_addr) < 0)
            errno_abort("send");
        printf("send: %s\n", sbuf);
        usleep(1000000/2);
    return 0;
}
