/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** socket_handle
*/

#ifndef SOCKET_HANDLE_H_
#define SOCKET_HANDLE_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "../../libs/myteams/logging_client.h"

typedef struct user_info_t {
    char user[33];
    char uuid[50];
} user_info;

int socket_handle(int port, char const *path);

#endif /* !SOCKET_HANDLE_H_ */
