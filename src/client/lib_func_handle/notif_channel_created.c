/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** notif_channel_created
*/

#include "socket_handle.h"

int client_event_channel_created_handle(char *buffer)
{
    char *channeluuid = var_parser(buffer, "channeluuid:");
    char *channelname = var_parser(buffer, "channelname:");
    char *channeldesc = var_parser(buffer, "channeldesc:");

    if (client_event_channel_created(channeluuid, channelname, channeldesc)
    == -1) {
        printf("Error in client_event_channel_created\n");
    }

    if (channeluuid) free(channeluuid);
    if (channelname) free(channelname);
    if (channeldesc) free(channeldesc);

    return 0;
}
