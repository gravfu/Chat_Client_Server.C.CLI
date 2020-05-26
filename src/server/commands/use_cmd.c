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

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static int check_context(int fd, command *cmd);

static int check_context_helper(int fd, command *cmd, channel_t *channel);

void change_context(connex_t *user_connex, command *cmd);

void use_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);

    if (contains_errors(fd, user_connex, cmd))
        return;
    change_context(user_connex, cmd);
    sprintf(rsp, "START_RSP\r\n%d: Successful context change.\r\nEND_RSP\r\n",
        RSP_USE);
    send_all(fd, rsp, strlen(rsp));
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.", fd);
        return (1);
    }
    if (cmd->num_args > 3) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.", fd);
        return (1);
    }
    return (check_context(fd, cmd));
}

static int check_context(int fd, command *cmd)
{
    channel_t *channel = NULL;
    team_t *team = NULL;

    if (cmd->num_args > 0) {
        team = find_team(NULL, cmd->args[0]);
        if (!team) {
            send_error(ERR_NOSUCHTEAM, "No such team exists.", fd);
            return (1);
        }
    }
    if (cmd->num_args > 1) {
        channel = find_channel(team->channels, NULL, cmd->args[1]);
        if (!channel) {
            send_error(ERR_NOSUCHCHANNEL, "No such channel exists.", fd);
            return (1);
        }
    }
    return (check_context_helper(fd, cmd, channel));
}

static int check_context_helper(int fd, command *cmd, channel_t *channel)
{
    thread_t *thread = NULL;

    if (cmd->num_args > 2) {
        thread = find_thread(channel->threads, NULL, cmd->args[2]);
        if (!thread) {
            send_error(ERR_NOSUCHTHREAD, "No such thread exists.", fd);
            return (1);
        }
    }
    return (0);
}

void change_context(connex_t *user_connex, command *cmd)
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