/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** lib_func_handle
*/

#include "socket_handle.h"

int client_event_loggedout_handle(char *buffer, user_info *info)
{
    char *user = var_parser(buffer, "username:");
    char *uuid = var_parser(buffer, "useruuid:");
    if (client_event_loggedout(user, uuid) == -1) {
        printf("Error in client_event_loggedin\n");
    }
    if (user)
        free(user);
    if (strcmp(uuid, info->uuid) == 0) {
        close(info->listenfd);
        if (uuid)
            free(uuid);
        exit (0);
    }
    if (uuid)
        free(uuid);
    return 0;
}