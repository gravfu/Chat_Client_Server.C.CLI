/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** socket_handle
*/

#include "socket_handle.h"

int user_parser(char *buffer)
{
    int read_var;
    memset(buffer, 0, 2048);
    write(0, "\n?>", 3);
    read_var = read(0, buffer, 2047);
    for (int i = 0; i < read_var; i++) {
        if (buffer[i] == ' ')
            buffer[i] = '\n';
    }
    return read_var;
}

int loop_client(int listenfd)
{
    int reader;
    int exit = 0;
    char buffer[2048];
    size_t size = 1024;
    int read_var = 2048;

    reader = read(listenfd, buffer, 1024);
    printf("%s", buffer);
    while (read_var > 0) { 
        read_var = user_parser(buffer);
        printf("BUFFER: %s\n", buffer);
        if (read_var > 1) {
            dprintf(listenfd, "START_COMM\r\n%s\r\nEND_COMM\n", buffer);
            memset(buffer, 0, sizeof(buffer));
            while (strstr(buffer, "END_CMD") == NULL && strstr(buffer, "END_RSP") == NULL && strstr(buffer, "500") == NULL) {
                reader = read(listenfd, buffer, 2047);
                if (reader > 1) {
                    printf("BUFFER: %s", buffer);
                }
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