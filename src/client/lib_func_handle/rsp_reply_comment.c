/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_reply_comment
*/

#include "socket_handle.h"

int client_print_reply_created_handle(char *buffer)
{
    char *threaduuid = var_parser(buffer, "threaduuid:");
    char *useruuid = var_parser(buffer, "useruuid:");
    char *time = var_parser(buffer, "time:");
    char *body = var_parser_body(buffer, "body:");
    time_t timea = string_to_time_t(time);

    if (client_print_reply_created(threaduuid, useruuid, timea, body) == -1) {
        printf("Error in client_print_reply_created\n");
    }
    if (threaduuid)
        free(threaduuid);
    if (useruuid)
        free(useruuid);
    if (time)
        free(time);
    if (body)
        free(body);
    return 0;
}