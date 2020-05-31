/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_info_channel
*/

#include "socket_handle.h"

int client_print_channel_handle(char *buffer)
{
    char *teamuuid = var_parser(buffer, "channeluuid:");
    char *teamname = var_parser(buffer, "channelname:");
    char *teamdesc = var_parser(buffer, "channeldesc:");

    if (client_print_channel(teamuuid, teamname, teamdesc) == -1) {
        printf("Error in client_print_channel\n");
    }
    if (teamuuid)
        free(teamuuid);
    if (teamname)
        free(teamname);
    if (teamdesc)
        free(teamdesc);
    return 0;
}