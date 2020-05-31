/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** messages_utils
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>

int user_exist(connex_t *user_connex, command_t *cmd)
{
    char rsp[256] = {0};
    user_t *user = find_user(NULL, cmd->args[0]);

    if (!user) {
        sprintf(rsp, "START_COMM\r\n%d\r\nuseruuid: \"%s\"\r\nEND_COMM\r\n",
            ERR_NOSUCHUSER, cmd->args[0]);
        send_direct(user_connex->sock_fd, rsp);
        return (0);
    }
    return (1);
}

int team_exist(connex_t *user_connex, command_t *cmd)
{
    char rsp[256] = {0};
    team_t *team = find_team(NULL, cmd->args[0]);

    if (!team) {
        sprintf(rsp, "START_COMM\r\n%d\r\nteamuuid: \"%s\"\r\nEND_COMM\r\n",
            ERR_NOSUCHTEAM, cmd->args[0]);
        send_direct(user_connex->sock_fd, rsp);
        return (0);
    }
    return (1);
}

int channel_exist(int sock_fd, command_t *cmd, team_t *team)
{
    char rsp[256] = {0};
    channel_t *channel = find_channel(team->channels, NULL, cmd->args[1]);

    if (!channel) {
        sprintf(rsp, "START_COMM\r\n%d\r\nchanneluuid: \"%s\"\r\nEND_COMM\r\n",
            ERR_NOSUCHCHANNEL, cmd->args[1]);
        send_direct(sock_fd, rsp);
        return (0);
    }
    return (1);
}

int thread_exist(int sock_fd, command_t *cmd, channel_t *channel)
{
    char rsp[256] = {0};
    thread_t *thread = find_thread(channel->threads, NULL, cmd->args[2]);

    if (!thread) {
        sprintf(rsp, "START_COMM\r\n%d\r\nthreaduuid: \"%s\"\r\nEND_COMM\r\n",
            ERR_NOSUCHTHREAD, cmd->args[2]);
        send_direct(sock_fd, rsp);
        return (0);
    }
    return (1);
}