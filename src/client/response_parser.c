/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** response_parser
*/

#include "socket_handle.h"
#include "return_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_code(char *buffer)
{
    char tmp2[5];
    char *tmp1 = strstr(buffer, "\n");
    strncpy(tmp2, tmp1 + 1, 3);
    tmp2[3] = '\0';
    return atoi(tmp2);
}

int err_parsing(int code, char *buffer)
{
    (void) code;
    (void) buffer;
    return 1;
}

int rsp_parsing(int code, char *buffer)
{
    if (code == RSP_USER)
        client_print_users_handle(buffer);
    else if (code == RSP_SUBSCRIBE)
        client_print_subscribed_handle(buffer);
    else if (code == RSP_UNSUBSCRIBE)
        client_print_unsubscribed_handle(buffer);
    else if (code == RSP_CREATE_COMMENT)
        client_print_reply_created_handle(buffer);
    else
        return 1;
    return 0;
}

int notif_parsing(int code, char *buffer)
{
    if (code == NOTIF_MSGRCV)
        client_event_private_message_received_handle(buffer);
    else if (code == NOTIF_TEAMCREATE)
        client_event_team_created_handle(buffer);
    else
        return 1;
    return 0;
}

void resp_parsing(char *buffer, user_info *info)
{
    int code = get_code(buffer);
    if (code == RSP_LOGIN)
        client_event_loggedin_handle(buffer, info);
    else if (code == RSP_LOGOUT)
        client_event_loggedout_handle(buffer, info);
    else if (notif_parsing(code, buffer) == 1 &&
            rsp_parsing(code, buffer) == 1 &&
            err_parsing(code, buffer) == 1)
        printf("%s", buffer);
}