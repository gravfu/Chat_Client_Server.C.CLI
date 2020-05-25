/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** switch_context
*/

#include "my_teams_srv.h"

void no_switch(connex_t *user_connex)
{
    user_connex->context = NULL;
    user_connex->team_cxt = 0;
    user_connex->channel_cxt = 0;
    user_connex->thread_cxt = 0;
}

void team_switch(connex_t *user_connex, command *cmd)
{
    team_t *team = find_team(NULL, cmd->args[0]);

    user_connex->context = team;
    user_connex->team_cxt = 1;
    user_connex->channel_cxt = 0;
    user_connex->thread_cxt = 0;
}

void channel_switch(connex_t *user_connex, command *cmd)
{
    team_t *team = find_team(NULL, cmd->args[0]);
    channel_t *channel = find_channel(team->channels, NULL, cmd->args[1]);

    user_connex->context = channel;
    user_connex->team_cxt = 1;
    user_connex->channel_cxt = 1;
    user_connex->thread_cxt = 0;
}

void thread_switch(connex_t *user_connex, command *cmd)
{
    team_t *team = find_team(NULL, cmd->args[0]);
    channel_t *channel = find_channel(team->channels, NULL, cmd->args[1]);
    thread_t *thread = find_thread(channel->threads, NULL, cmd->args[2]);

    user_connex->context = thread;
    user_connex->team_cxt = 1;
    user_connex->channel_cxt = 1;
    user_connex->thread_cxt = 1;
}