/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_list_thread
*/

#include "socket_handle.h"

int client_channel_print_threads_handle(char *buffer)
{
    char *tmp = strstr(buffer, "\n") + 1;
    char *t_uuid = var_parser(tmp, "threaduuid:");
    char *u_uuid = var_parser(tmp, "useruuid:");
    char *title = var_parser(tmp, "threadtitle:");
    char *body = var_parser_body(tmp, "body:");
    time_t time = string_to_time_t(var_parser(tmp, "time:"));

    tmp = strstr(tmp, "\n") + 1;
    while(t_uuid != NULL) {
        if (client_channel_print_threads(t_uuid, u_uuid, time, title, body) == -1)
            printf("Error in client_channel_print_threads\n");
        if (t_uuid != NULL) free(t_uuid);
        if (u_uuid != NULL) free(u_uuid);
        if (title != NULL) free(title);
        if (body != NULL) free(body);
        tmp = strstr(tmp, "\n") + 1;
        t_uuid = var_parser(tmp, "threaduuid:");
        u_uuid = var_parser(tmp, "useruuid:");
        title = var_parser(tmp, "threadtitle:");
        body = var_parser_body(tmp, "body:");
        time = string_to_time_t(var_parser(tmp, "time:"));
    }
    return 0;
}
