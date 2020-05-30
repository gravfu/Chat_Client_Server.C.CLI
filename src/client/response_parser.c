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
    switch (code) {
        case RSP_USER:
        return client_print_users_handle(buffer);
        case RSP_SUBSCRIBE:
        return client_print_subscribed_handle(buffer);
        case RSP_UNSUBSCRIBE:
        return client_print_unsubscribed_handle(buffer);
        case RSP_CREATE_COMMENT:
        return client_print_reply_created_handle(buffer);
        default:
        return 1;
    }
}

int notif_parsing(int code, char *buffer)
{
    switch (code) {
        case NOTIF_MSGRCV:
        return client_event_private_message_received_handle(buffer);
        case NOTIF_TEAMCREATE:
        return client_event_team_created_handle(buffer);
        case NOTIF_THREADMSG:
        return client_event_thread_message_received_handle(buffer);
        case NOTIF_CHANCREATE:
        return client_event_channel_created_handle(buffer);
        case NOTIF_THREADCREATE:
        return client_event_thread_created_handle(buffer);
        default:
        return 1;
    }
}

void resp_parsing(char *buffer, user_info *info)
{
    int code = get_code(buffer);
    switch (code) {
        case RSP_LOGIN:
        client_event_loggedin_handle(buffer, info);
        break;
        case RSP_LOGOUT:
        client_event_loggedout_handle(buffer, info);
        break;
        default:
        if (notif_parsing(code, buffer) == 1 && rsp_parsing(code, buffer) == 1
            && err_parsing(code, buffer) == 1)
            printf("%s", buffer);
    }
}
