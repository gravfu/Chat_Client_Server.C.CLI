/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** notify_many
*/

#include "my_teams_srv.h"

void notify_team(team_t *team, const char *message)
{
    user_t *users = team->subs;

    while (users != NULL) {
        add_notification(users, message);
        users = users->next;
    }
}

void notify_connected(const char *message)
{
    const connex_t *connected = get_connex();

    while (connected != NULL) {
        if (connected->logged_in && connected->user)
            add_notification(connected->user, message);
        connected = connected->next;
    }
}

void notify_domain(const char *message)
{
    const user_t *users = get_users();

    while (users != NULL) {
        add_notification(users, message);
        users = users->next;
    }
}