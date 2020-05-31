/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_list_team
*/

#include "socket_handle.h"

int client_print_teams_handle(char *buffer)
{
    char *tmp = strstr(buffer, "\n") + 1;
    char *name = var_parser(tmp, "teamname:");
    char *uuid = var_parser(tmp, "teamuuid:");
    char *desc = var_parser(tmp, "teamdesc:");

    tmp = strstr(tmp, "\n") + 1;
    while(name != NULL) {
        if (client_print_teams(uuid, name, desc) == -1)
            printf("Error in client_print_teams\n");
        if (name != NULL) free(name);
        name = NULL;
        if (uuid != NULL) free(uuid);
        if (desc != NULL) free(desc);
        tmp = strstr(tmp, "\n") + 1;
        name = var_parser(tmp, "teamname:");
        uuid = var_parser(tmp, "teamuuid:");
        desc = var_parser(tmp, "teamdesc:");
    }
    return 0;
}
