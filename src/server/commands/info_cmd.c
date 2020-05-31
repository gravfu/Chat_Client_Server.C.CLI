/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

static char *get_info(connex_t *user_connex);

static void send_info_responses(connex_t *user_connex, char *str);

void info_cmd(int fd, command_t *cmd)
{
    char *str = NULL;
    connex_t *user_connex = find_connex(fd);

    if (contains_errors(fd, user_connex, cmd))
        return;
    str = get_info(user_connex);
    send_info_responses(user_connex, str);
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

static char *get_info(connex_t *user_connex)
{
    char *info = NULL;

    if (user_connex->thread_cxt) {
        info = get_thread_str((thread_t *)user_connex->context);
        return (info);
    }
    if (user_connex->channel_cxt) {
        info = get_channel_str((channel_t *)user_connex->context);
        return (info);
    }
    if (user_connex->team_cxt) {
        info = get_team_str((team_t *)user_connex->context);
        return (info);
    }
    info = get_user_str(user_connex->user);
    return (info);
}

static void send_info_responses(connex_t *user_connex, char *str)
{
    if (user_connex->thread_cxt) {
        info_thread_response(user_connex, str);
        return;
    }
    if (user_connex->channel_cxt) {
        info_channel_response(user_connex, str);
        return;
    }
    if (user_connex->team_cxt) {
        info_user_response(user_connex, str);
        return;
    }
    info_user_response(user_connex, str);
}