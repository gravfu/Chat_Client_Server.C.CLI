/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** rsp_messages_command
*/

#include "socket_handle.h"

int client_private_message_print_messages_handle(char *buffer)
{
    char *tmp = strstr(buffer, "\n") + 1;
    char *useruuid = var_parser(tmp, "useruuid:");
    char *time = var_parser(tmp, "time:");
    time_t timea = string_to_time_t(time);
    char *body = var_parser_body(tmp, "body:");

    tmp = strstr(tmp, "\n") + 1;
    while (useruuid != NULL) {
        if (client_private_message_print_messages(useruuid, timea, body) == -1)
            printf("Error in client_print_users\n");
        if (useruuid != NULL) free(useruuid);
        if (time != NULL) free(time);
        if (body != NULL) free(body);
        tmp = strstr(tmp, "\n") + 1;
        useruuid = var_parser(tmp, "useruuid:");
        time = var_parser(tmp, "time:");
        timea = string_to_time_t(time);
        body = var_parser_body(tmp, "body:");
    }
    return 0;
}