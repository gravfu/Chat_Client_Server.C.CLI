/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** send_all
*/

#include "my_teams_srv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void send_all(int client_fd, const char *buffer, int len)
{
    int rem = len;
    int sent = 0;
    int total = 0;

    while (rem != 0) {
        sent = write(client_fd, buffer + total, rem);
        if (sent == -1) {
            perror("write");
            exit(84);
        }
        total += sent;
        rem -= sent;
    }
}

void send_error(int error_num, int client_fd)
{
    char err_msg[256] = {0};

    sprintf(err_msg, "START_RSP\r\n%d\r\nEND_RSP\r\n", error_num);
    send_all(client_fd, err_msg, strlen(err_msg));
}

int send_to_user(const connex_t *connections, const notification_t *notif,
    fd_set *write_fds)
{
    const char *u_name = NULL;
    const char *u_uuid = NULL;
    int found = 0;

    while (connections != NULL) {
        if (connections->user && connections->logged_in &&
            FD_ISSET(connections->sock_fd, write_fds) &&
            strcmp(connections->user->user_name, notif->rcvr->user_name)
            == 0 &&
            strcmp(connections->user->user_uuid, notif->rcvr->user_uuid)
            == 0) {
            send_all(connections->sock_fd, notif->msg, notif->msg_len);
            found = 1;
        }
        connections = connections->next;
    }
    return (found);
}

void send_responses(fd_set *write_fds)
{
    const connex_t *connections = get_connex();
    const notification_t *notifs = get_notifications();
    const notification_t *temp = NULL;

    while (notifs) {
        if (send_to_user(connections, notifs, write_fds)) {
            temp = notifs;
            notifs = notifs->next;
            del_notification(temp);
            continue;
        }
        notifs = notifs->next;
    }
}