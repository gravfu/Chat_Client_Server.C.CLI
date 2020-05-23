/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** connex_list_manips
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void alloc_connex(connex_t **list, int fd);

static int found_space(int fd);

void add_connex(int fd)
{
    connex_t *list_cpy = connect_list;
    connex_t *new_connex = NULL;

    if (connect_list == NULL)
        alloc_connex(&connect_list, fd);
    else {
        if (found_space(fd)) return;
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_connex(&new_connex, fd);
        list_cpy->next = new_connex;
    }
}

static void alloc_connex(connex_t **list, int fd)
{
    if ((*list = malloc(sizeof(connex_t))) == NULL) {
        perror("malloc");
        exit(84);
    }
    (*list)->sock_fd = fd;
    (*list)->logged_in = 0;
    (*list)->user = NULL;
    memset((*list)->context, 0, 4096);
    (*list)->team_cxt = 0;
    (*list)->channel_cxt = 0;
    (*list)->thread_cxt = 0;
    (*list)->next = NULL;
}

static int found_space(int fd)
{
    connex_t *list_cpy = connect_list;

    while (list_cpy != NULL) {
        if (list_cpy->sock_fd == -1) {
            list_cpy->sock_fd = fd;
            list_cpy->logged_in = 0;
            list_cpy->user = NULL;
            memset(list_cpy->context, 0, 4096);
            list_cpy->team_cxt = 0;
            list_cpy->channel_cxt = 0;
            list_cpy->thread_cxt = 0;
            return (1);
        }
        list_cpy = list_cpy->next;
    }
    return (0);
}

void delete_conn(int fd)
{
    connex_t *list_cpy = connect_list;

    while (list_cpy != NULL) {
        if (list_cpy->sock_fd == fd) {
            list_cpy->sock_fd = -1;
            list_cpy->logged_in = 0;
            list_cpy->user = NULL;
            memset(list_cpy->context, 0, 4096);
            list_cpy->team_cxt = 0;
            list_cpy->channel_cxt = 0;
            list_cpy->thread_cxt = 0;
            return;
        }
        list_cpy = list_cpy->next;
    }
}

connex_t *find_connex(int fd)
{
    connex_t *list_cpy = connect_list;

    while (list_cpy != NULL) {
        if (list_cpy->sock_fd == fd) {
            return (list_cpy);
        }
        list_cpy = list_cpy->next;
    }
    return (NULL);
}