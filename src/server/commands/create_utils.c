/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_utils
*/

#include "logging_server.h"
#include "my_teams_srv.h"
#include <stddef.h>
#include <string.h>

void create_comment(connex_t *user_connex, command_t *cmd)
{
    char time_str[TIME_LEN] = {0};
    time_t now = time(NULL);
    thread_t *thread_context = (thread_t *)(user_connex->context);

    strftime(time_str, TIME_LEN, "%Y-%m-%d %H:%M:%S", localtime(&now));
    add_comment(thread_context, user_connex->user->user_uuid, cmd->args[0]);
    server_event_thread_new_message(thread_context->thread_uuid,
        user_connex->user->user_uuid, cmd->args[0]);
    create_comment_response(user_connex, cmd, time_str);
}

void create_thread(connex_t *user_connex, command_t *cmd, const char *uuid_str)
{
    char time_str[TIME_LEN] = {0};
    time_t now = time(NULL);
    channel_t *channel_context = (channel_t *)(user_connex->context);
    thread_t new_thread;

    strftime(time_str, TIME_LEN, "%Y-%m-%d %H:%M:%S", localtime(&now));
    memset(new_thread.thread_title, 0, MAX_NAME_LENGTH + 1);
    strcpy(new_thread.thread_title, cmd->args[0]);
    strcpy(new_thread.thread_uuid, uuid_str);
    memset(new_thread.thread_init, 0, MAX_BODY_LENGTH + 1);
    strcpy(new_thread.thread_init, cmd->args[1]);
    strcpy(new_thread.timestamp, time_str);
    strcpy(new_thread.user_uuid, user_connex->user->user_uuid);
    new_thread.p_channel = channel_context;
    add_thread(channel_context, &new_thread);
    create_thread_file(user_connex, &new_thread);
    server_event_thread_created(channel_context->channel_uuid, uuid_str,
        user_connex->user->user_uuid, cmd->args[1]);
    create_thread_response(uuid_str, user_connex);
}

void create_channel(connex_t *user_connex, command_t *cmd,
    const char *uuid_str)
{
    team_t *team_context = (team_t *)(user_connex->context);

    add_chann(team_context, cmd->args[0], uuid_str, cmd->args[1]);
    create_channel_dir(team_context, cmd->args[0], uuid_str, cmd->args[1]);
    server_event_channel_created(team_context->team_uuid, uuid_str,
        cmd->args[0]);
    create_channel_response(uuid_str, user_connex);
}

void create_team(connex_t *user_connex, command_t *cmd, const char *uuid_str)
{
    add_team(cmd->args[0], uuid_str, cmd->args[1]);
    create_team_dir(cmd->args[0], uuid_str, cmd->args[1]);
    server_event_team_created(uuid_str, cmd->args[0],
        user_connex->user->user_uuid);
    create_team_response(uuid_str, user_connex);
}