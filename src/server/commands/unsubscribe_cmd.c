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

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static int err_check_helper(int fd, connex_t *user_connex, command *cmd);

void unsubscribe_cmd(int fd, command *cmd)
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
    sprintf(rsp, "START_RSP\r\n%d\r\nEND_RSP\r\n", RSP_UNSUBSCRIBE);
    send_all(fd, rsp, strlen(rsp));
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    team_t *team = NULL;

    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.", fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, "Missing paramters.", fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.", fd);
        return (1);
    }
    return (err_check_helper(fd, user_connex, cmd));
}

static int err_check_helper(int fd, connex_t *user_connex, command *cmd)
{
    team_t *team = find_team(NULL, cmd->args[0]);
    user_t *sub = NULL;

    if (!team) {
        send_error(ERR_NOSUCHTEAM, "No such team exists.", fd);
        return (1);
    }
    sub = find_sub(team->subs, NULL, user_connex->user->user_uuid);
    if (!sub) {
        send_error(ERR_NOTSUBBED, "Not subscribed to team.", fd);
        return (1);
    }
    return (0);
}