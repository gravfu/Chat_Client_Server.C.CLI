/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_thread_created
*/

#include "socket_handle.h"

int client_print_team_created_handle(char *buffer)
{
    char *teamuuid = var_parser(buffer, "teamuuid:");
    char *teamname = var_parser(buffer, "teamname:");
    char *teamdesc = var_parser(buffer, "teamdesc:");

    if (client_print_team_created(teamuuid, teamname, teamdesc) == -1) {
        printf("Error in client_event_team_created\n");
    }
    if (teamuuid)
        free(teamuuid);
    if (teamname)
        free(teamname);
    if (teamdesc)
        free(teamdesc);
    return 0;
}