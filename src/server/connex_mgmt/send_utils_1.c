/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_utils_1
*/

#include "my_teams_srv.h"

void send_responses()
{
    const connex_t *connections = get_connex();
    const notification_t *notifs = get_notifications();
    const notification_t *temp = NULL;

    while (notifs) {
        if (send_to_user(connections, notifs)) {
            temp = notifs;
            notifs = notifs->next;
            del_notification(temp);
            continue;
        }
        notifs = notifs->next;
    }
}

