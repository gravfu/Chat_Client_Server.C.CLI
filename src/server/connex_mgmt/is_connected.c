/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** is_connected
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <string.h>

int is_connected(const user_t *user)
{
    const connex_t *connections = get_connex();

    while (connections != NULL) {
        if (connections->logged_in &&
            strcmp(user->user_name, connections->user->user_name) == 0 &&
            strcmp(user->user_name, connections->user->user_name) == 0) {
            return (1);
        }
        connections = connections->next;
    }
    return (0);
}