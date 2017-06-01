//
// Created by Li Qiang on 01/06/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static const int MAXLINE = 1023;

int main(int argc, char **argv)
{
    int socketfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        printf("usage: daytime_client <IPaddress>");
        exit(-1);
    }

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        printf("socket error");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s", argv[1]);
        exit(-1);
    }

    if (connect(socketfd, (const sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error");
        exit(-1);
    }

    while ((n = read(socketfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
        {
            printf("fputs error");
            exit(-1);
        }
    }
    if (n < 0)
    {
        printf("read error");
        exit(-1);
    }

    return 0;
}
