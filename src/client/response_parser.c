/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** response_parser
*/

#include "socket_handle.h"

void resp_parsing(char *buffer, user_info *info)
{
    if (strstr(buffer, "503") != NULL)
        client_event_loggedin_handle(buffer, info);
    else if (strstr(buffer, "504") != NULL)
        client_event_loggedout_handle(info);
    else
        printf("%s", buffer);
}