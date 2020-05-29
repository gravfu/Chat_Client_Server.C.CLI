/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "my_teams_srv.h"
#include "server.h"
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

static void check_for_update(int connex_fd, int listen_fd, int *fd_max,
    fd_set *child_set[2]);

static void handle_event(int fd, int *fd_max, fd_set *child_set[2]);

void launch_server(char *port)
{
    fd_set read_fds;
    fd_set write_fds;
    int fd_max;
    int listen_fd = get_sock(port);
    fd_set *child_set[2] = {NULL, NULL};
    fd_set *master_set[2] = {&master_read, &master_write};

    listen_for_conn(listen_fd);
    FD_ZERO(master_set[0]);
    FD_ZERO(master_set[1]);
    FD_SET(listen_fd, master_set[0]);
    fd_max = listen_fd;
    while (1) {
        read_fds = master_read;
        write_fds = master_write;
        child_set[0] = &read_fds;
        child_set[1] = &write_fds;
        monitor_fds(&fd_max, child_set, master_set);
        for (int i = 0; i <= fd_max; i++)
            check_for_update(i, listen_fd, &fd_max, child_set);
    }
}

static void check_for_update(int connex_fd, int listen_fd, int *fd_max,
    fd_set *child_set[2])
{
    int client_fd;
    struct sockaddr_storage client_addr;

    if (FD_ISSET(connex_fd, child_set[0])) {
        if (connex_fd == listen_fd) {
            client_fd = accept_conn(listen_fd, &client_addr);
            FD_SET(client_fd, &master_read);
            FD_SET(client_fd, &master_write);
            add_connex(client_fd);
            *fd_max = (client_fd > *fd_max) ? client_fd : *fd_max;
            send_all(client_fd, "Welcome to Epitech's TPC Server\n", 32);
        } else handle_event(connex_fd, fd_max, child_set);
    }
}

static void handle_event(int fd, int *fd_max, fd_set *child_set[2])
{
    command_t cmd_in;

    new_recv(fd, &cmd_in);
    if (strlen(cmd_in.cmd) == 0) {
        FD_CLR(fd, child_set[0]);
        FD_CLR(fd, child_set[1]);
        FD_CLR(fd, &master_read);
        FD_CLR(fd, &master_write);
        close(fd);
        delete_conn(fd);
        *fd_max = (fd == *fd_max) ? (*fd_max - 1) : *fd_max;
    } else {
        respond(fd, &cmd_in);
        send_responses(child_set[1]);
    }
}