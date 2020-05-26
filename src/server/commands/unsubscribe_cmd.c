/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** unsubscribe_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static int err_check_helper(int fd, connex_t *user_connex, command *cmd);

static int drop_sub(team_t *team, const char *sub_name, const char *sub_uuid);

static void drop_sub_helper(FILE *sub_info, FILE *sub_info_tmp,
    const char *sub_name, const char *sub_uuid);

void unsubscribe_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    team_t *team = NULL;

    if (contains_errors(fd, user_connex, cmd))
        return;
    team = find_team(NULL, cmd->args[0]);
    del_sub(&(team->subs), user_connex->user->user_name,
        user_connex->user->user_uuid);
    drop_sub(team, user_connex->user->user_name, user_connex->user->user_uuid);
    sprintf(rsp, "START_RSP\r\n%d: %s %s.\r\nEND_RSP\r\n", RSP_UNSUBSCRIBE,
        "Successfully unsubscribed from", team->team_name);
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
    if (!sub) {
        send_error(ERR_NOTSUBBED, "Not subscribed to team.", fd);
        return (1);
    }
    return (0);
}

static int drop_sub(team_t *team, const char *sub_name, const char *sub_uuid)
{
    const char *info_format = "./backup/teams/team_%s/sub_info";
    const char *tmp_format = "./backup/teams/team_%s/sub_info_tmp";
    char sub_info_path[4096];
    char sub_info_tmp_path[4096];
    char s_name[MAX_NAME_LENGTH + 1];
    char s_uuid[UUID_STR_LEN];
    FILE *sub_info = NULL;
    FILE *sub_info_tmp = NULL;

    sprintf(sub_info_path, info_format, team->team_uuid);
    sprintf(sub_info_tmp_path, tmp_format, team->team_uuid);
    sub_info = fopen(sub_info_path, "r");
    sub_info_tmp = fopen(sub_info_tmp_path, "w+");
    if (sub_info && sub_info_tmp) {
        drop_sub_helper(sub_info, sub_info_tmp, sub_name, sub_uuid);
        fclose(sub_info);
        fclose(sub_info_tmp);
        remove(sub_info_path);
        rename(sub_info_tmp_path, sub_info_path);
    }
}

static void drop_sub_helper(FILE *sub_info, FILE *sub_info_tmp,
    const char *sub_name, const char *sub_uuid)
{
    char s_name[MAX_NAME_LENGTH + 1];
    char s_uuid[UUID_STR_LEN];
    const char *sub_format = "name: \"%[^\"]\" uuid: \"%[^\"]\"\n";

    while (fscanf(sub_info, sub_format, s_name, s_uuid) == 2) {
        if (strcmp(s_name, sub_name) != 0 && strcmp(s_uuid, sub_uuid) != 0) {
            fprintf(sub_info_tmp, "name: \"%s\" uuid: \"%s\"\n", s_name,
                s_uuid);
        }
        memset(s_name, 0, MAX_NAME_LENGTH);
        memset(s_uuid, 0, UUID_STR_LEN);
    }
}