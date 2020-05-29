/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** notification_manips
*/

#include "my_teams_srv.h"
#include "notifications.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void alloc_notif(notification_t **list, const user_t *rcvr,
    const char *msg);

void add_notification(const user_t *rcvr, const char *msg)
{
    notification_t *list_cpy = notif_list;
    notification_t *new_notif = NULL;

    if (notif_list == NULL)
        alloc_notif(&notif_list, rcvr, msg);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_notif(&new_notif, rcvr, msg);
        list_cpy->next = new_notif;
    }
}

static void alloc_notif(notification_t **list, const user_t *rcvr,
    const char *msg)
{
    if ((*list = malloc(sizeof(notification_t))) == NULL) {
        perror("malloc");
        exit(84);
    }
    if (!msg) {
        free(*list);
        return;
    }
    (*list)->msg = strdup(msg);
    (*list)->msg_len = strlen(msg);
    (*list)->rcvr = rcvr;
    (*list)->next = NULL;
}

void del_notification(const notification_t *to_delete)
{
    notification_t *prev = NULL;
    notification_t *temp = notif_list;

    if (temp != NULL && temp == to_delete) {
        notif_list = temp->next;
        free(temp->msg);
        free(temp);
        return;
    }
    while (temp != NULL && temp != to_delete) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp->msg);
    free(temp);
}

const notification_t *get_notifications()
{
    return (notif_list);
}