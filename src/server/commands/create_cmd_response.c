/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_cmd_response
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <stddef.h>

void create_comment_response(connex_t *user_connex, command_t *cmd,
    const char *timestamp)
{
    char rsp[1024] = {0};
    char notif[1024] = {0};
    thread_t *thread = (thread_t *)user_connex->context;

    sprintf(rsp, "START_RSP\r\n%d\r\nthreaduuid: \"%s\" useruuid: \"%s\" "
        "time: \"%s\" body: \"%s\"\r\nEND_RSP\r\n", RSP_CREATE_COMMENT,
        thread->thread_uuid, user_connex->user->user_uuid, timestamp,
        cmd->args[0]);
    sprintf(notif, "START_RSP\r\n%d\r\nteamuuid: \"%s\" threaduuid: \"%s\" "
        "useruuid: \"%s\" body: \"%s\"\r\nEND_RSP\r\n",
        NOTIF_THREADCREATE, thread->p_channel->p_team->team_uuid,
        thread->thread_uuid, user_connex->user->user_uuid, cmd->args[0]);
    send_direct(user_connex->sock_fd, rsp);
    notify_team(thread->p_channel->p_team, notif, user_connex->user);
}

void create_thread_response(const char *uuid_str, connex_t *user_connex)
{
    char rsp[1024] = {0};
    char notif[1024] = {0};
    channel_t *channel = (channel_t *)user_connex->context;
    thread_t *thread = find_thread(channel->threads, NULL, uuid_str);

    sprintf(rsp, "START_RSP\r\n%d\r\nthreaduuid: \"%s\" useruuid: \"%s\" "
        "time: \"%s\" title: \"%s\" body: \"%s\"\r\nEND_RSP\r\n",
        RSP_CREATE_THREAD, uuid_str, user_connex->user->user_uuid,
        thread->timestamp, thread->thread_title, thread->thread_init);
    sprintf(notif, "START_RSP\r\n%d\r\nthreaduuid: \"%s\" useruuid: \"%s\" "
        "time: \"%s\" title: \"%s\" body: \"%s\"\r\nEND_RSP\r\n",
        NOTIF_THREADCREATE, uuid_str, user_connex->user->user_uuid,
        thread->timestamp, thread->thread_title, thread->thread_init);
    send_direct(user_connex->sock_fd, rsp);
    notify_team(channel->p_team, notif, user_connex->user);
}

void create_channel_response(const char *uuid_str, connex_t *user_connex)
{
    char rsp[1024] = {0};
    char notif[1024] = {0};
    team_t *team = (team_t *)user_connex->context;
    channel_t *channel = find_channel(team->channels, NULL, uuid_str);

    sprintf(rsp, "START_RSP\r\n%d\r\nchanneluuid: \"%s\" channelname: \"%s\" "
        "channeldesc: \"%s\"\r\nEND_RSP\r\n", RSP_CREATE_CHANNNEL, uuid_str,
        channel->channel_name, channel->channel_desc);
    sprintf(notif, "START_RSP\r\n%d\r\nchanneluuid: \"%s\" channelname: \"%s\""
        " channeldesc: \"%s\"\r\nEND_RSP\r\n", NOTIF_CHANCREATE, uuid_str,
        channel->channel_name, channel->channel_desc);
    send_direct(user_connex->sock_fd, rsp);
    notify_team(team, notif, user_connex->user);
}

void create_team_response(const char *uuid_str, connex_t *user_connex)
{
    char rsp[1024] = {0};
    char notif[1024] = {0};
    team_t *team = find_team(NULL, uuid_str);

    sprintf(rsp, "START_RSP\r\n%d\r\nteamuuid: \"%s\" teamname: \"%s\" "
        "teamdesc: \"%s\"\r\nEND_RSP\r\n", RSP_CREATE_TEAM, uuid_str,
        team->team_name, team->team_desc);
    sprintf(notif, "START_RSP\r\n%d\r\nteamuuid: \"%s\" teamname: \"%s\" "
        "teamdesc: \"%s\"\r\nEND_RSP\r\n", NOTIF_TEAMCREATE, uuid_str,
        team->team_name, team->team_desc);
    send_direct(user_connex->sock_fd, rsp);
    notify_domain(notif, user_connex->user);
}