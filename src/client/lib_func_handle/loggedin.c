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

    if (info->is_set == 0) {
        strcpy(info->user, user);
        strcpy(info->uuid, uuid);
        info->is_set = 1;
    }
    if (client_event_loggedin(uuid, user) == -1) {
        printf("Error in client_event_loggedin\n");
    }
    if (user)
        free(user);
    if (uuid)
        free(uuid);
    return 0;
}