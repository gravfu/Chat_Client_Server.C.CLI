/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_user
*/

#include "socket_handle.h"

int client_print_users_handle(char *buffer)
{
    char *user = var_parser(buffer, "username:");
    char *uuid = var_parser(buffer, "useruuid:");
    char *status = var_parser(buffer, "status:");

    if (client_print_users(uuid, user, atoi(status)) == -1) {
        printf("Error in client_print_users\n");
    }
    if (user != NULL)
        free(user);
    if (uuid != NULL)
        free(uuid);
    if (status != NULL)
        free(status);
    return 0;
}