/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribe_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static int err_check_helper(int fd, connex_t *user_connex, command *cmd);

static void subscribe(connex_t *user_connex, team_t *team);

void subscribe_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    team_t *team = NULL;

    if (contains_errors(fd, user_connex, cmd))
        return;
    team = find_team(NULL, cmd->args[0]);
    subscribe(user_connex, team);
    sprintf(rsp, "START_RSP\r\n%d: %s %s.\r\nEND_RSP\r\n", RSP_SUBSCRIBE,
        "Successfully subscribed to", team->team_name);
    send_all(fd, rsp, strlen(rsp));
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    team_t *team = NULL;

    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.", fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, "Missing paramters.", fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.", fd);
        return (1);
    }
    return (err_check_helper(fd, user_connex, cmd));
}

static int err_check_helper(int fd, connex_t *user_connex, command *cmd)
{
    team_t *team = find_team(NULL, cmd->args[0]);
    user_t *sub = NULL;

    if (!team) {
        send_error(ERR_NOSUCHTEAM, "No such team exists.", fd);
        return (1);
    }
    sub = find_sub(team->subs, NULL, user_connex->user->user_uuid);
    if (sub) {
        send_error(ERR_ALREADYSUBBED, "Already subscribed.", fd);
        return (1);
    }
    return (0);
}

static void subscribe(connex_t *user_connex, team_t *team)
{
    char sub_info_path[4096];
    const char *format = "./backup/teams/team_%s/sub_info";
    const char *sub_format = "name: \"%s\" uuid: \"%s\"\n";
    FILE *sub_info = NULL;

    add_sub(team, user_connex->user->user_name, user_connex->user->user_uuid);
    sprintf(sub_info_path, format, team->team_uuid);
    sub_info = fopen(sub_info_path, "a+");
    if (sub_info) {
        fprintf(sub_info, sub_format, user_connex->user->user_name,
            user_connex->user->user_uuid);
        fclose(sub_info);
    }
}