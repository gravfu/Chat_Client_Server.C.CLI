/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe_cmd
*/

#include "logging_server.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static int err_check_helper(int fd, connex_t *user_connex, command *cmd);

static void subscribe(connex_t *user_connex, team_t *team);

static void subscribe_helper(const char *sub_info_path,
    const char *team_sub_info_path, connex_t *user_connex, team_t *team);

void subscribe_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    team_t *team = NULL;

    if (contains_errors(fd, user_connex, cmd))
        return;
    team = find_team(NULL, cmd->args[0]);
    subscribe(user_connex, team);
    server_event_user_join_a_team(team->team_uuid,
        user_connex->user->user_uuid);
    sprintf(rsp, "START_RSP\r\n%d\r\nEND_RSP\r\n", RSP_SUBSCRIBE);
    send_all(fd, rsp, strlen(rsp));
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    return (err_check_helper(fd, user_connex, cmd));
}

static int err_check_helper(int fd, connex_t *user_connex, command *cmd)
{
    team_t *team = find_team(NULL, cmd->args[0]);
    user_t *sub = NULL;

    if (!team) {
        send_error(ERR_NOSUCHTEAM, fd);
        return (1);
    }
    sub = find_sub(team->subs, NULL, user_connex->user->user_uuid);
    if (sub) {
        send_error(ERR_ALREADYSUBBED, fd);
        return (1);
    }
    return (0);
}

static void subscribe(connex_t *user_connex, team_t *team)
{
    char sub_info_path[4096] = {0};
    char team_sub_info_path[4096] = {0};
    const char *team_p_format = "./backup/teams/team_%s/sub_info";
    const char *user_p_format = "./backup/users/usr_%s/team_sub_info";

    add_sub(team, user_connex->user->user_name, user_connex->user->user_uuid);
    sprintf(sub_info_path, team_p_format, team->team_uuid);
    sprintf(team_sub_info_path, user_p_format, user_connex->user->user_uuid);
    subscribe_helper(sub_info_path, team_sub_info_path, user_connex, team);
}

static void subscribe_helper(const char *sub_info_path,
    const char *team_sub_info_path, connex_t *user_connex, team_t *team)
{
    const char *sub_format = "name: \"%s\" uuid: \"%s\"\n";
    const char *team_sub_format = "name: \"%s\" uuid: \"%s\" desc: \"%s\"\n";
    FILE *sub_info = NULL;
    FILE *team_sub_info = NULL;

    sub_info = fopen(sub_info_path, "a+");
    team_sub_info = fopen(team_sub_info_path, "a+");
    if (sub_info && team_sub_info) {
        fprintf(sub_info, sub_format, user_connex->user->user_name,
            user_connex->user->user_uuid);
        fprintf(team_sub_info, team_sub_format, team->team_name,
            team->team_uuid, team->team_desc);
        fclose(sub_info);
        fclose(team_sub_info);
    }
}