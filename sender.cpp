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
    struct sockaddr_in send_addr;
    int trueflag = 1;
    int fd;

    if(argc != 4) {
        printf("Usage: sender ip_address port message\n");
        printf("submitted parameters [%d]:\n", argc);
        for(int i=0;i<argc;i++)
            printf("\t%s\n", argv[i]);
        return 0;
    }

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        errno_abort("socket");
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof trueflag) < 0)
        errno_abort("setsockopt");

    memset(&send_addr, 0, sizeof send_addr);
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = (in_port_t) htons(atoi(argv[2]));
    inet_aton(argv[1], &send_addr.sin_addr);

    if (sendto(fd, argv[3], strlen(argv[3]), 0, (struct sockaddr*) &send_addr, sizeof send_addr) < 0)
        errno_abort("sendto");

    printf("sent: %s\n", argv[3]);    

    return 0;
}
