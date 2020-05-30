/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** err_unknown_team
*/

#include "socket_handle.h"

int client_error_unknown_team_handle(char *buffer)
{
    char *user = var_parser(buffer, "teamuuid:");
    if (client_error_unknown_team(user) == -1) {
        printf("Error in client_event_loggedin\n");
    }
    if (user)
        free(user);
    return 0;
}