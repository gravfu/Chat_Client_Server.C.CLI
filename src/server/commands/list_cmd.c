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

void list_cmd(int fd, command_t *cmd)
{
    char *rsp = NULL;
    char *str = NULL;
    connex_t *user_connex = find_connex(fd);
    unsigned int len_str = 0;
    unsigned int rsp_len = 0;

    if (contains_errors(fd, user_connex, cmd))
        return;
    str = get_list(user_connex);
    len_str = (str != NULL) ? strlen(str) : len_str;
    rsp_len = strlen("START_RSP\r\n") + strlen("000: Listing:\r\n") +
        len_str + strlen("END_RSP\r\n");
    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST, str);
    if (str) free(str);
    send_all(fd, rsp, strlen(rsp));
    free(rsp);
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