/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_thread_created
*/

#include "socket_handle.h"

int client_print_thread_created_handle(char *buffer)
{
    char *threaduuid = var_parser(buffer, "threaduuid:");
    char *useruuid = var_parser(buffer, "useruuid:");
    char *time = var_parser(buffer, "time:");
    time_t timea = string_to_time_t(time);
    char *title = var_parser(buffer, "title:");
    char *body = var_parser_body(buffer, "body:");

    if (client_print_thread_created(threaduuid, useruuid,
        timea, title, body) == -1)
        printf("Error in client_event_team_created\n");
    if (threaduuid) free(threaduuid);
    if (useruuid) free(useruuid);
    if (time) free(time);
    if (title) free(title);
    if (body) free(body);
    return 0;
}