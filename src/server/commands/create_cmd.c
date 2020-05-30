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

static void create(const char *uuid_str, connex_t *user_connex,
    command_t *cmd);

static int is_duplicate(int fd, connex_t *user_connex, command_t *cmd);

void create_cmd(int fd, command_t *cmd)
{
    char uuid_str[UUID_STR_LEN] = {0};
    connex_t *user_connex = find_connex(fd);
    uuid_t uuid;

    if (contains_errors(fd, user_connex, cmd))
        return;
    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    create(uuid_str, user_connex, cmd);
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
    return (is_duplicate(fd, user_connex, cmd));
}

static int is_duplicate(int fd, connex_t *user_connex, command_t *cmd)
{
    if (user_connex->channel_cxt) {
        channel_t * channel_context = (channel_t *)(user_connex->context);
        if (find_thread(channel_context->threads, cmd->args[0], NULL)
            != NULL) {
            send_error(ERR_THREADEXISTS, fd);
            return (1);
        }
    } else if (user_connex->team_cxt) {
        team_t *team_context = (team_t *)(user_connex->context);
        if (find_channel(team_context->channels, cmd->args[0], NULL) != NULL) {
            send_error(ERR_CHANNELEXISTS, fd);
            return (1);
        }
    } else {
        if (find_team(cmd->args[0], NULL) != NULL) {
            send_error(ERR_TEAMEXISTS, fd);
            return (1);
        }
    }
    return (0);
}

static void create(const char *uuid_str, connex_t *user_connex,
    command_t *cmd)
{
    char time_str[TIME_LEN] = {0};
    time_t now = time(NULL);

    strftime(time_str, TIME_LEN, "%Y-%m-%d %H:%M:%S", localtime(&now));
    if (user_connex->thread_cxt) {
        create_comment(user_connex, cmd);
    } else if (user_connex->channel_cxt) {
        create_thread(user_connex, cmd, uuid_str);
    }
    if (user_connex->team_cxt && !user_connex->channel_cxt) {
        create_channel(user_connex, cmd, uuid_str);
    } else if (!user_connex->team_cxt && !user_connex->channel_cxt &&
        !user_connex->thread_cxt) {
        create_team(user_connex, cmd, uuid_str);
    }
}