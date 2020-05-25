/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <uuid/uuid.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static void create(int fd, connex_t *user_connex, command *cmd);

static void create_helper(connex_t *user_connex, command *cmd,
    const char *uuid_str);

void create_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);

    if (contains_errors(fd, user_connex, cmd))
        return;
    create(fd, user_connex, cmd);
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.", fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, "Missing parameters.", fd);
        return (1);
    }
    if (cmd->num_args > 2) {
        send_error(ERR_TOOMANYPARAMS, "Too many parameters.", fd);
        return (1);
    }
    if (cmd->num_args == 1 && !user_connex->thread_cxt) {
        send_error(ERR_NEEDMOREPARAMS, "Missing parameters.", fd);
        return (1);
    }
    if (cmd->num_args > 1 && user_connex->thread_cxt) {
        send_error(ERR_TOOMANYPARAMS, "Too many parameters.", fd);
        return (1);
    }
    return (0);
}

// static int is_duplicate(int fd, connex_t *user_connex, command *cmd)
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

static void create(int fd, connex_t *user_connex, command *cmd)
{
    char uuid_str[37];
    uuid_t uuid;
    channel_t *channel_context = NULL;
    thread_t *thread_context = NULL;

    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    if (user_connex->thread_cxt) {
        thread_context = (thread_t *)(user_connex->context);
        create_comment(thread_context, user_connex->user->user_name,
            cmd->args[0]);
            return;
    }
    if (user_connex->channel_cxt) {
        channel_context = (channel_t *)(user_connex->context);
        add_thread(channel_context, cmd->args[0], uuid_str, cmd->args[1]);
        create_thread_file(channel_context, cmd->args[0], uuid_str,
            cmd->args[1]);
        return;
    }
    create_helper(user_connex, cmd, uuid_str);
}

static void create_helper(connex_t *user_connex, command *cmd,
    const char *uuid_str)
{
    team_t *team_context = NULL;

    if (user_connex->team_cxt) {
        team_context = (team_t *)(user_connex->context);
        add_chann(team_context, cmd->args[0], uuid_str,
            cmd->args[1]);
        create_channel_dir(team_context, cmd->args[0], uuid_str, cmd->args[1]);
        return;
    }
    if (!user_connex->team_cxt && !user_connex->channel_cxt &&
        !user_connex->thread_cxt) {
        add_team(cmd->args[0], uuid_str, cmd->args[1]);
        create_team_dir(cmd->args[0], uuid_str, cmd->args[1]);
        return;
    }
}