/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** notify_many
*/

#include "my_teams_srv.h"
#include <string.h>

void notify_team(team_t *team, const char *message, user_t *ignore)
{
    user_t *users = team->subs;

    while (users != NULL) {
        if (!ignore || strcmp(ignore->user_uuid, users->user_uuid) != 0)
            add_notification(users, message);
        users = users->next;
    }
}

void notify_connected(const char *message, user_t *ignore)
{
    const connex_t *connected = get_connex();

    while (connected != NULL) {
        if (connected->logged_in && connected->user &&
        (!ignore || strcmp(ignore->user_uuid, connected->user->user_uuid)))
            add_notification(connected->user, message);
        connected = connected->next;
    }
}

void notify_domain(const char *message, user_t *ignore)
{
    const user_t *users = get_users();

    while (users != NULL) {
        if (!ignore || strcmp(ignore->user_uuid, users->user_uuid) != 0)
            add_notification(users, message);
        users = users->next;
    }
}