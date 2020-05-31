/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

static char *get_list(connex_t *user_connex);

static void send_list_responses(connex_t *user_connex, char *str);

void list_cmd(int fd, command_t *cmd)
{
    char *str = NULL;
    connex_t *user_connex = find_connex(fd);

    if (contains_errors(fd, user_connex, cmd))
        return;
    str = get_list(user_connex);
    send_list_responses(user_connex, str);
    if (str) free(str);
}

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd)
{
    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args != 0) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    return (0);
}

static char *get_list(connex_t *user_connex)
{
    char *list = NULL;

    if (user_connex->thread_cxt) {
        list = get_comments_str(user_connex);
        return (list);
    }
    if (user_connex->channel_cxt) {
        list = get_threads_str(user_connex);
        return (list);
    }
    if (user_connex->team_cxt) {
        list = get_channels_str(user_connex);
        return (list);
    }
    list = get_teams_str();
    return (list);
}

static void send_list_responses(connex_t *user_connex, char *str)
{
    if (user_connex->thread_cxt) {
        list_comments_response(user_connex, str);
        return;
    }
    if (user_connex->channel_cxt) {
        list_threads_response(user_connex, str);
        return;
    }
    if (user_connex->team_cxt) {
        list_channels_response(user_connex, str);
        return;
    }
    list_teams_response(user_connex, str);
}

