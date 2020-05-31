/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_list_thread
*/

#include "socket_handle.h"

void client_channel_print_threads_handle_loop(char *tmp, char *threaduuid,
    char *useruuid, char *time, char *title, char *body, time_t timestamp)
{
    while(threaduuid != NULL) {
        if (client_channel_print_threads(threaduuid, useruuid, timestamp,
            title, body) == -1) {
            printf("Error in client_channel_print_threads\n");
        }
        if (threaduuid != NULL) free(threaduuid);
        threaduuid = NULL;
        if (useruuid != NULL) free(useruuid);
        if (time != NULL) free(time);
        if (title != NULL) free(title);
        if (body != NULL) free(body);
        tmp = strstr(tmp, "\n") + 1;
        threaduuid = var_parser(tmp, "threaduuid:");
        useruuid = var_parser(tmp, "useruuid:");
        time = var_parser(tmp, "time:");
        title = var_parser(tmp, "threadtitle:");
        body = var_parser_body(tmp, "body:");
        timestamp = string_to_time_t(time);
    }
}

int client_channel_print_threads_handle(char *buffer)
{
    char *tmp = strstr(buffer, "\n") + 1;
    char *threaduuid = var_parser(tmp, "threaduuid:");
    char *useruuid = var_parser(tmp, "useruuid:");
    char *time = var_parser(tmp, "time:");
    char *title = var_parser(tmp, "threadtitle:");
    char *body = var_parser_body(tmp, "body:");
    time_t timestamp = string_to_time_t(time);

    tmp = strstr(tmp, "\n") + 1;
    client_channel_print_threads_handle_loop(tmp, threaduuid, useruuid, time,
        title, body, timestamp);
    return 0;
}
