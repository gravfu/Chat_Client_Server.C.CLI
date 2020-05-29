/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_cmd
*/

#include "logging_server.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

static void create(const char *uuid_str, connex_t *user_connex, command_t *cmd);

static void create_helper(connex_t *user_connex, command_t *cmd,
    const char *uuid_str);

void create_cmd(int fd, command_t *cmd)
{
    char rsp[256] = {0};
    char uuid_str[UUID_STR_LEN] = {0};
    connex_t *user_connex = find_connex(fd);
    uuid_t uuid;

    if (contains_errors(fd, user_connex, cmd))
        return;
    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    create(uuid_str, user_connex, cmd);
    sprintf(rsp, "START_RSP\r\n%d\r\nEND_RSP\r\n", RSP_USE);
    send_all(fd, rsp, strlen(rsp));
}

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd)
{
    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, fd);
        return (1);
    }
    if (cmd->num_args > 2) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    if (cmd->num_args == 1 && !user_connex->thread_cxt) {
        send_error(ERR_NEEDMOREPARAMS, fd);
        return (1);
    }
    if (cmd->num_args > 1 && user_connex->thread_cxt) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    return (0);
}

// static int is_duplicate(int fd, connex_t *user_connex, command_t *cmd)
// {
//     channel_t *channel_context = NULL;
//     team_t *team_context = NULL;
//     thread_t *thread_context = NULL;

//     if (user_connex->channel_cxt) {
//         channel_context = (channel_t *)(user_connex->context);
//         if (find_thread(channel_context->threads, cmd->args[0], NULL) != NULL) {
//             send_error(ERR_THREADEXISTS, "Team already exists.\n", fd);
//             return (1);
//         }
//     }
//     if (user_connex->team_cxt) {
//         team_context = (team_t *)(user_connex->context);
//         if (find_channel(team_context->channels, cmd->args[0], NULL) != NULL) {
//             send_error(ERR_CHANNELEXISTS, "Channel already exists.\n", fd);
//             return (1);
//         }
//     }
//     if (!user_connex->team_cxt && !user_connex->channel_cxt &&
//         !user_connex->thread_cxt) {
//         if (find_team(cmd->args[0], NULL) != NULL) {
//             send_error(ERR_CHANNELEXISTS, "Channel already exists.\n", fd);
//             return (1);
//         }
//         send_error(ERR_TEAMEXISTS, "Team already exists.\n", fd);
//         return (1);
//     }

//     // if (cmd->num_args == 1 && !user_connex->thread_cxt) {
//     //     send_error(ERR_NEEDMOREPARAMS, "Missing parameters.\n", fd);
//     //     return (1);
//     // }
//     // if (user_connex->team_cxt) {

//     // }
//     // if (user_connex->channel_cxt) {

//     // }
//     // if (user_connex->thread_cxt) {

//     // }
// }

static void create(const char *uuid_str, connex_t *user_connex,
    command_t *cmd)
{
    if (user_connex->thread_cxt) {
        thread_t *thread_context = (thread_t *)(user_connex->context);
        create_comment(thread_context, user_connex->user->user_uuid,
            cmd->args[0]);
        server_event_thread_new_message(thread_context->thread_uuid,
            user_connex->user->user_uuid, cmd->args[0]);
        return;
    } else if (user_connex->channel_cxt) {
        channel_t *channel_context = (channel_t *)(user_connex->context);
        char time_str[TIME_LEN];
        time_t now = time(NULL);
        strftime(time_str, TIME_LEN, "%Y-%m-%d %H:%M:%S", localtime(&now));
        set_parent_chan(channel_context);
        add_thread(cmd->args[0], uuid_str, cmd->args[1], time_str);
        create_thread_file(user_connex, cmd->args[0], uuid_str, cmd->args[1]);
        server_event_thread_created(channel_context->channel_uuid, uuid_str,
            user_connex->user->user_uuid, cmd->args[1]);
        return;
    }
    create_helper(user_connex, cmd, uuid_str);
}

static void create_helper(connex_t *user_connex, command_t *cmd,
    const char *uuid_str)
{
    if (user_connex->team_cxt) {
        team_t *team_context = (team_t *)(user_connex->context);
        add_chann(team_context, cmd->args[0], uuid_str, cmd->args[1]);
        create_channel_dir(team_context, cmd->args[0], uuid_str, cmd->args[1]);
        server_event_channel_created(team_context->team_uuid, uuid_str,
            cmd->args[0]);
        return;
    }
    if (!user_connex->team_cxt && !user_connex->channel_cxt &&
        !user_connex->thread_cxt) {
        add_team(cmd->args[0], uuid_str, cmd->args[1]);
        create_team_dir(cmd->args[0], uuid_str, cmd->args[1]);
        server_event_team_created(uuid_str, cmd->args[0],
            user_connex->user->user_uuid);
        return;
    }
}