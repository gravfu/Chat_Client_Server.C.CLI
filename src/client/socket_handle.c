/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** socket_handle
*/

#include "socket_handle.h"

int loop_client(int listenfd)
{
    int reader;
    int exit = 0;
    int read_var = 1024;
    char *buffer = NULL;
    size_t size = 1024;

    while (exit == 0 && read_var > 0) {
        memset(buffer, 0, sizeof(buffer));
        read_var = getline(&buffer, &size, stdin);
        if (read_var > 1) {
            dprintf(listenfd, "%s", buffer);
            memset(buffer, 0, sizeof(buffer));
            reader = read(listenfd, buffer, 1024);
            if (reader > 1) {
                printf("BUFFER: %s\n", buffer);
            }
        }
    }
}

int socket_handle(int port, char const *ip)
{
    int listenfd;
    struct sockaddr_in serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        printf("Socket Error\n");
        return 84;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("IP not correct\n");
        return 84;
    }
    if (connect(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error while connecting to server\n");
        return 84;
    }
    return loop_client(listenfd);
}