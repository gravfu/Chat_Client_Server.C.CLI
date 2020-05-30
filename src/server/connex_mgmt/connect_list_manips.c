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

void add_connex(int fd)
{
    connex_t *list_cpy = connect_list;
    connex_t *new_connex = NULL;

    if (connect_list == NULL)
        alloc_connex(&connect_list, fd);
    else {
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
    (*list)->context = NULL;
    (*list)->user = NULL;
    (*list)->team_cxt = 0;
    (*list)->channel_cxt = 0;
    (*list)->thread_cxt = 0;
    (*list)->next = NULL;
}

void delete_conn(int fd)
{
    connex_t *prev = NULL;
    connex_t *temp = connect_list;

    if (temp != NULL && temp->sock_fd == fd) {
        connect_list = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->sock_fd != fd) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
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

const connex_t *get_connex(void)
{
    return (connect_list);
}