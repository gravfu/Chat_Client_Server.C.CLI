/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** err_unknown_channel
*/

#include "socket_handle.h"

int client_error_unknown_channel_handle(char *buffer)
{
    char *user = var_parser(buffer, "channeluuid:");
    if (client_error_unknown_channel(user) == -1) {
        printf("Error in client_event_loggedin\n");
    }
    if (user)
        free(user);
    return 0;
}