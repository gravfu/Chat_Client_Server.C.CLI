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
    int sent;
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

void send_error(int error_num, const char *msg, int client_fd)
{
    char err_msg[256] = {0};

    sprintf(err_msg, "%d: %s", error_num, msg);
    send_all(client_fd, err_msg, strlen(err_msg));
}