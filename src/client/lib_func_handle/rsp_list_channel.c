/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_list_channel
*/

#include "socket_handle.h"

int client_team_print_channels_handle(char *buffer)
{
    char *tmp = strstr(buffer, "\n") + 1;
    char *name = var_parser(tmp, "channelname:");
    char *uuid = var_parser(tmp, "channeluuid:");
    char *desc = var_parser(tmp, "channeldesc:");

    tmp = strstr(tmp, "\n") + 1;
    while(name != NULL) {
        if (client_team_print_channels(uuid, name, desc) == -1)
            printf("Error in client_team_print_channels\n");
        if (name != NULL) free(name);
        name = NULL;
        if (uuid != NULL) free(uuid);
        if (desc != NULL) free(desc);
        tmp = strstr(tmp, "\n") + 1;
        name = var_parser(tmp, "channelname:");
        uuid = var_parser(tmp, "channeluuid:");
        desc = var_parser(tmp, "channeldesc:");
    }
    return 0;
}
