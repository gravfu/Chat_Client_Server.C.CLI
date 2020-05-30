/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** notif_thread_created
*/

#include "socket_handle.h"

int client_event_thread_created_handle(char *buffer)
{
    char *threaduuid = var_parser(buffer, "threaduuid:");
    char *useruuid = var_parser(buffer, "useruuid:");
    char *time = var_parser(buffer, "time:");
    char *title = var_parser(buffer, "title:");
    char *body = var_parser_body(buffer, "body:");

    time_t timestamp = string_to_time_t(time);

    if (client_event_thread_created(threaduuid, useruuid, timestamp, title,
        body) == -1) {
        printf("Error in client_event_thread_created\n");
    }

    if (threaduuid) free(threaduuid);
    if (useruuid) free(useruuid);
    if (time) free(time);
    if (title) free(title);
    if (body) free(body);

    return 0;
}
