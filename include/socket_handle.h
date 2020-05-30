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
#include "parser_func.h"

typedef struct user_info_t {
    char user[33];
    char uuid[50];
    int is_set;
    int listenfd;
} user_info;

int socket_handle(int port, char const *path);
int client_event_loggedin_handle(char *buffer, struct user_info_t *info);
int client_event_loggedout_handle(char *buffer, struct user_info_t *info);
int client_event_private_message_received_handle(char *buffer);
int client_print_users_handle(char *buffer);
int client_event_team_created_handle(char *buffer);
void resp_parsing(char *buffer, user_info *info);

#endif /* !SOCKET_HANDLE_H_ */
