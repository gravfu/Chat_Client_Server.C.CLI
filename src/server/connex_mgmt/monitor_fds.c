/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** monitor_fds
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void monitor_fds(int *fd_max, fd_set *child_sets[2], fd_set *master_sets[2])
{
    fd_set *read_fds = child_sets[0];
    fd_set *write_fds = child_sets[1];
    fd_set *master_read = master_sets[0];
    fd_set *master_write = master_sets[1];
    struct stat stat_buf;

    for (int i = 0; i <= *fd_max; i++) {
        if (fstat(i, &stat_buf) == -1) {
            FD_CLR(i, read_fds);
            FD_CLR(i, master_read);
            FD_CLR(i, write_fds);
            FD_CLR(i, master_write);
            delete_conn(i);
            *fd_max = (i == *fd_max) ? (*fd_max - 1) : *fd_max;
        }
    }
    select(*fd_max + 1, read_fds, write_fds, NULL, NULL);
}