/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "my_teams_srv.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void check_for_update(int fds[2], int *fd_max, fd_set *read_fds,
    fd_set *master);

static void handle_event(int fd, int *fd_max, fd_set *read_fds, fd_set *master);

void launch_server(char *port)
{
    fd_set master;
    fd_set read_fds;
    int fd_max;
    int listen_fd = get_sock(port);
    int fds[2];

    listen_for_conn(listen_fd);
    FD_ZERO(&master);
    FD_SET(listen_fd, &master);
    fd_max = listen_fd;
    fds[1] = listen_fd;
    while (1) {
        read_fds = master;
        monitor_fds(&fd_max, &read_fds, &master);
        for (int i = 0; i <= fd_max; i++) {
            fds[0] = i;
            check_for_update(fds, &fd_max, &read_fds, &master);
        }
    }
}

static void check_for_update(int fds[2], int *fd_max, fd_set *read_fds,
    fd_set *master)
{
    int client_fd;
    int connex_fd = fds[0];
    int listen_fd = fds[1];
    struct sockaddr_storage client_addr;

    if (FD_ISSET(connex_fd, read_fds)) {
        if (connex_fd == listen_fd) {
            client_fd = accept_conn(listen_fd, &client_addr);
            FD_SET(client_fd, master);
            add_connex(client_fd);
            *fd_max = (client_fd > *fd_max) ? client_fd : *fd_max;
            send_all(client_fd, "Welcome to Epitech's TPC Server\n", 32);
        } else handle_event(fds[0], fd_max, read_fds, master);
    }
}

static void handle_event(int fd, int *fd_max, fd_set *read_fds, fd_set *master)
{
    command cmd_in;

    new_recv(fd, &cmd_in);
    if (strlen(cmd_in.cmd) == 0) {
        FD_CLR(fd, read_fds);
        FD_CLR(fd, master);
        close(fd);
        delete_conn(fd);
        *fd_max = (fd == *fd_max) ? (*fd_max - 1) : *fd_max;
    } else
        respond(fd, &cmd_in);
}