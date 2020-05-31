/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_info_channel
*/

#include "socket_handle.h"

int client_print_thread_handle(char *buffer)
{
    char *threaduuid = var_parser(buffer, "threaduuid:");
    char *useruuid = var_parser(buffer, "useruuid:");
    char *time = var_parser(buffer, "time:");
    time_t timea = string_to_time_t(time);
    char *threadname = var_parser(buffer, "threadname:");
    char *body = var_parser_body(buffer, "body:");

    if (client_print_thread(threaduuid, useruuid, timea, threadname, body) == -1) {
        printf("Error in client_print_thread\n");
    }
    if (threaduuid) free(threaduuid);
    if (useruuid) free(useruuid);
    if (time) free(time);
    if (threadname) free(threadname);
    if (body) free(body);
    return 0;
}