/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** rsp_channel_created
*/

#include "socket_handle.h"

int client_event_channel_created_handle(char *buffer)
{
    char *channeluuid = var_parser(buffer, "channeluuid:");
    char *channelname = var_parser(buffer, "channelname:");
    char *channeldesc = var_parser(buffer, "channeldesc:");

    return 0;
}
