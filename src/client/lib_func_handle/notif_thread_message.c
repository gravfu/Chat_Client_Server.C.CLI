/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** notif_thread_message
*/

#include "socket_handle.h"

int client_event_thread_message_received_handle(char *buffer)
{
    char *teamuuid = var_parser(buffer, "teamuuid:");
    char *threaduuid = var_parser(buffer, "threaduuid:");
    char *useruuid = var_parser(buffer, "useruuid:");
    char *message = var_parser_body(buffer, "body:");

    if (client_event_thread_message_received(teamuuid, threaduuid, useruuid,
        message) == -1)
        printf("Error in client_event_thread_message_received\n");
    if (teamuuid != NULL) free(teamuuid);
    if (threaduuid != NULL) free(threaduuid);
    if (useruuid != NULL) free(useruuid);
    if (message != NULL) free(message);
    return 0;
}
