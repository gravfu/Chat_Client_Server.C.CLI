/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** err_client_exist
*/

#include "socket_handle.h"

int client_error_already_exist_handle(char *buffer, user_info *info)
{
    if (client_error_already_exist() == -1) {
        printf("Error in client_event_loggedin\n");
    }
    return 0;
}