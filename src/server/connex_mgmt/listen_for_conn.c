/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** listen_for_conn
*/

#include "my_teams_srv.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

void listen_for_conn(int listen_fd)
{
    if (listen(listen_fd, MAX_PENDING) == -1) {
        perror("listen");
        exit(84);
    }
}