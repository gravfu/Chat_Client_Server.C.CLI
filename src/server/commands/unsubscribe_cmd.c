/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe_cmd
*/

#include "logging_server.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

static int err_check_helper(int fd, connex_t *user_connex, command_t *cmd);

void unsubscribe_cmd(int fd, command_t *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    team_t *team = NULL;

    if (contains_errors(fd, user_connex, cmd))
        return;
    team = find_team(NULL, cmd->args[0]);
    del_sub(&(team->subs), user_connex->user->user_name,
        user_connex->user->user_uuid);
    drop_sub(team, user_connex->user->user_name, user_connex->user->user_uuid);
    drop_team_sub(user_connex->user, team->team_name, team->team_uuid);
    server_event_user_leave_a_team(team->team_uuid,
        user_connex->user->user_uuid);
    sprintf(rsp, "START_RSP\r\n%d\r\nuseruuid: \"%s\" teamuuid: \"%s\"\r\n"
        "END_RSP\r\n", RSP_UNSUBSCRIBE, user_connex->user->user_uuid,
        team->team_uuid);
    send_direct(user_connex->sock_fd, rsp);
}

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd)
{
    team_t *team = NULL;

    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    return (err_check_helper(fd, user_connex, cmd));
}

static int err_check_helper(int fd, connex_t *user_connex, command_t *cmd)
{
    team_t *team = find_team(NULL, cmd->args[0]);
    user_t *sub = NULL;

    if (!team_exist(user_connex, cmd))
        return (1);
    sub = find_sub(team->subs, NULL, user_connex->user->user_uuid);
    if (!sub) {
        send_error(ERR_NOTSUBBED, fd);
        return (1);
    }
    return (0);
}