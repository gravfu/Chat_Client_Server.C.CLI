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

/*int user_parser(char *buffer, int listenfd)
{
    int read_var;
    memset(buffer, 0, 2048);
    write(0, "\n?>", 3);
    read_var = read(0, buffer, 2047);
    for (int i = 0; i < read_var; i++) {
        if (buffer[i] == ' ')
            buffer[i] = '\n';
    }
    if (read_var > 1)
            dprintf(listenfd, "START_COMM\r\n%s\r\nEND_COMM\n", buffer);
    return 0;
}*/

int client_event_loggedin_handle(char *buffer, user_info *info)
{
    char *user = var_parser(buffer, "username:");
    char *uuid = var_parser(buffer, "useruuid:");

    strcpy(info->user, user);
    strcpy(info->uuid, uuid);
    printf("You are connected as %s\nYour UUID is: %s\n", user, uuid);
    if (client_event_loggedin(uuid, user) != 1) {
        printf("Error in client_event_loggedin\n");
    }
    return 0;
}

void parsing(char *buffer, user_info *info, char *cmd)
{
    if (strstr(buffer, "503") != NULL && strstr(cmd, "login") != NULL)
        client_event_loggedin_handle(buffer, info);
}

int read_output(int listenfd, char *cmd, user_info *info)
{
    char buffer[20001];
    int reader;
    memset(buffer, 0, sizeof(buffer));
    reader = read(listenfd, buffer, sizeof(buffer));
    if (reader > 0) {
        printf("BUFFER: %s", buffer);
        parsing(buffer, info, cmd);
    } else if (reader == 0) {
        printf("Connection closed by foreign host.\n");
        exit(0);
    } else {
        printf("Error while reading data.\n");
    }
    return 0;
}
int socket_data_detected(char *buffer, int listenfd_socket, user_info *info)
{
    read_output(listenfd_socket, buffer, info);
    return 0;
}

int stdin_data_detected(char *buffer, int listenfd_socket)
{
    int read_var;
    memset(buffer, 0, 2048);
    read_var = read(0, buffer, sizeof(buffer));
    for (int i = 0; i < read_var; i++) {
        if (buffer[i] == ' ')
            buffer[i] = '\n';
    }
    if (read_var > 1)
        dprintf(listenfd_socket, "START_COMM\r\n%s\r\nEND_COMM\n", buffer);
    return 0;
}

int loop_client_a(int listenfd)
{
    int reader_sel;
    char buffer[2048];
    user_info info;
    // Select
    fd_set rfds_stdin;
    fd_set rfds_set;
    FD_ZERO(&rfds_stdin);
    FD_SET(0, &rfds_stdin);
    FD_SET(listenfd, &rfds_stdin);
    printf("fd: %d\n", listenfd);
    write(0, "\n?>", 3);
    memset(buffer, 0, sizeof(buffer));
    while (1) {
        rfds_set = rfds_stdin;
        reader_sel = select(listenfd+1, &rfds_set, NULL, NULL, NULL);
        if (reader_sel < 0)
            printf("select failed\n ");
        if (reader_sel > 0) {
            if (FD_ISSET(0, &rfds_set))
                stdin_data_detected(buffer, listenfd);
            if (FD_ISSET(listenfd, &rfds_set))
                socket_data_detected(buffer, listenfd, &info);
            
        }
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
    if (connect(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error while connecting to server\n");
        return 84;
    }
    return loop_client_a(listenfd);
}