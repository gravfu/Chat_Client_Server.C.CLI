/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** lib_func_handle
*/

#include "socket_handle.h"

int client_event_private_message_received_handle(char *buffer)
{
    char *uuid = var_parser(buffer, "useruuid:");
    char *body = var_parser_body(buffer, "body:");
    if (client_event_private_message_received(uuid, body) == -1)
        printf("Error in client_event_private_message\n");
    if (body != NULL)
        free(body);
    if (uuid != NULL)
        free(uuid);
    return 0;
}