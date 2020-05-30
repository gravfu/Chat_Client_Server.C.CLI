/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_team_created
*/

#include "socket_handle.h"

int client_print_unsubscribed_handle(char *buffer)
{
    char *useruuid = var_parser(buffer, "useruuid:");
    char *teamuuid = var_parser(buffer, "teamuuid:");

    if (client_print_subscribed(useruuid, teamuuid) == -1) {
        printf("Error in client_event_team_created\n");
    }
    if (useruuid)
        free(useruuid);
    if (teamuuid)
        free(teamuuid);
    return 0;
}