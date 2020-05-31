/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_user
*/

#include "socket_handle.h"

int client_print_users_handle(char *buffer)
{
    char *tmp = strstr(buffer, "\n") + 1;
    char *user = var_parser(tmp, "username:");
    char *uuid = var_parser(tmp, "useruuid:");
    char *status = var_parser(tmp, "status:");

    tmp = strstr(tmp, "\n") + 1;
    while (user != NULL) {
        if (client_print_users(uuid, user, atoi(status)) == -1)
            printf("Error in client_print_users\n");
        if (user != NULL) free(user);
        user = NULL;
        if (uuid != NULL) free(uuid);
        if (status != NULL) free(status);
        tmp = strstr(tmp, "\n") + 1;
        user = var_parser(tmp, "username:");
        uuid = var_parser(tmp, "useruuid:");
        status = var_parser(tmp, "status:");
    }
    return 0;
}
