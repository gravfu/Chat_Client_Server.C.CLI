/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** socket_handle
*/

#include "socket_handle.h"
#include "parser_func.h"
#include <sys/select.h>
#include <sys/types.h>

int read_output(int listenfd, user_info *info)
{
    char buffer[20001];
    int reader;
    memset(buffer, 0, sizeof(buffer));
    reader = read(listenfd, buffer, sizeof(buffer));
    if (reader > 0) {
        resp_parsing(buffer, info);
    } else if (reader == 0) {
        printf("Connection closed by foreign host.\n");
        exit(0);
    } else {
        printf("Error while reading data.\n");
    }
    return 0;
}

int stdin_data_detected(char *buffer, int listenfd_socket)
{
    int read_var;
    int tmp = 0;
    memset(buffer, 0, 4096);
    read_var = read(0, buffer, 4096);
    if (read_var > 1) {
        for (int i = 0; i < read_var; i++) {
            if (buffer[i] == '"')
                tmp++;
            if (buffer[i] == ' ' && tmp % 2 == 0)
                buffer[i] = '\n';
        }
        remove_char(buffer, '"');
        printf("BUFFER: %s\n", buffer);
        dprintf(listenfd_socket, "START_COMM\r\n%s\r\nEND_COMM\n", buffer);
    } else if (read_var == 0) {
        return 1;
    }
    return 0;
}

void loop_content(fd_set *rfds_set, user_info *info, int *tmp, char *buffer)
{
    int reader_sel = select(info->listenfd + 1, rfds_set, NULL, NULL, NULL);

    if (reader_sel < 0)
        printf("select failed\n ");
    if (reader_sel > 0) {
        if (FD_ISSET(info->listenfd, rfds_set))
            read_output(info->listenfd, info);
        if (FD_ISSET(0, rfds_set) && *tmp == 0)
            *tmp = stdin_data_detected(buffer, info->listenfd);
        if (*tmp == 2)
            *tmp = 4;
        if (*tmp == 1) {
            sleep(0.01);
            *tmp = 2;
        }
    }
}

int loop_init(int const listenfd)
{
    user_info info;
    int tmp = 0;
    fd_set rfds_stdin;
    fd_set rfds_set;
    char buffer[4097];

    FD_ZERO(&rfds_stdin);
    FD_SET(0, &rfds_stdin);
    FD_SET(listenfd, &rfds_stdin);
    info.listenfd = listenfd;
    read_output(listenfd, &info);
    while (tmp != 4) {
        rfds_set = rfds_stdin;
        loop_content(&rfds_set, &info, &tmp, buffer);
    }
    return 0;
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
    if (connect(listenfd, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0) {
        printf("Error while connecting to server\n");
        return 84;
    }
    return loop_init(listenfd);
}