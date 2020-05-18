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

int socket_handle(int port, char const *path);

#endif /* !SOCKET_HANDLE_H_ */
