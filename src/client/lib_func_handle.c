/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** lib_func_handle
*/

#include "socket_handle.h"

int client_event_loggedin_handle(char *buffer, user_info *info)
{
    char *user = var_parser(buffer, "username:");
    char *uuid = var_parser(buffer, "useruuid:");

    strcpy(info->user, user);
    strcpy(info->uuid, uuid);
    if (client_event_loggedin(uuid, user) != 1) {
        printf("Error in client_event_loggedin\n");
    }
    if (user)
        free(user);
    if (uuid)
        free(uuid);
    return 0;
}

int client_event_loggedout_handle(user_info *info)
{
    if (client_event_loggedout(info->uuid, info->user) != 1) {
        printf("Error in client_event_loggedin\n");
    }
    return 0;
}