/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** use_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

static int check_context(int fd, connex_t *user_connex, command_t *cmd);

static int check_context_helper(int fd, command_t *cmd, team_t *team);

void change_context(connex_t *user_connex, command_t *cmd);

void use_cmd(int fd, command_t *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);

    if (contains_errors(fd, user_connex, cmd))
        return;
    change_context(user_connex, cmd);
    sprintf(rsp, "START_RSP\r\n%d\r\nEND_RSP\r\n", RSP_USE);
    send_direct(user_connex->sock_fd, rsp);
}

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd)
{
    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args > 3) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    return (check_context(fd, user_connex, cmd));
}

static int check_context(int fd, connex_t *user_connex, command_t *cmd)
{
    team_t *team = NULL;

    if (cmd->num_args > 0) {
        if (!team_exist(user_connex, cmd))
            return (1);
        team = find_team(NULL, cmd->args[0]);
        if (find_team_sub(user_connex->user->team_subs, team->team_name,
            team->team_uuid) == NULL) {
            send_error(ERR_NOTSUBBED, fd);
            return (1);
        }
    }
    return (check_context_helper(fd, cmd, team));
}

static int check_context_helper(int fd, command_t *cmd, team_t *team)
{
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    if (cmd->num_args > 1) {
        if (!channel_exist(fd, cmd, team))
            return (1);
        channel = find_channel(team->channels, NULL, cmd->args[1]);
    }
    if (cmd->num_args > 2) {
        if (!thread_exist(fd, cmd, channel))
            return (1);
    }
    return (0);
}

void change_context(connex_t *user_connex, command_t *cmd)
{
    switch (cmd->num_args) {
    case 0:
        no_switch(user_connex);
        break;
    case 1:
        team_switch(user_connex, cmd);
        break;
    case 2:
        channel_switch(user_connex, cmd);
        break;
    case 3:
        thread_switch(user_connex, cmd);
        break;
    default:
        break;
    }
}