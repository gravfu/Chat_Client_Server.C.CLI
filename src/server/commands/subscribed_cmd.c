/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** subscribed
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

char *get_sub_teams(connex_t *user_connex);

char *get_sub_users(command *cmd);

void subscribed_cmd(int fd, command *cmd)
{
    char *rsp = NULL;
    char *str = NULL;
    connex_t *user_connex = find_connex(fd);
    unsigned int len_str = 0;
    unsigned int rsp_len = 0;

    if (contains_errors(fd, user_connex, cmd)) return;
    if (cmd->args == 0)
        str = get_sub_teams(user_connex);
    else
        str = get_sub_users(cmd);
    len_str = (str != NULL) ? strlen(str) : len_str;
    rsp_len = strlen("START_RSP\r\n") + len_str + strlen("END_RSP\r\n");
    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%s\r\nEND_RSP\r\n", RSP_SUBSCRIBED, str);
    if (str) free(str);
    send_all(fd, rsp, strlen(rsp));
    free(rsp);
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    team_t *team = NULL;

    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    if (cmd->num_args == 1) {
        team = find_team(NULL, cmd->args[0]);
        if (!team) {
            send_error(ERR_NOSUCHTEAM, fd);
            return (1);
        }
    }
    return (0);
}

char *get_sub_teams(connex_t *user_connex)
{
    char buff[128] = {0};
    char *all_sub_teams = NULL;
    team_t *team_subs = user_connex->user->team_subs;
    unsigned int length = 0;

    for (int i = 0; team_subs != NULL; i++) {
        sprintf(buff, "\tteam name: \"%s\" team uuid: \"%s\"\r\n",
            team_subs->team_name, team_subs->team_uuid);
        length += strlen(buff);
        all_sub_teams = realloc(all_sub_teams, length * sizeof(char));
        if (i == 0)
            memset(all_sub_teams, 0, length * sizeof(char));
        strcat(all_sub_teams, buff);
        memset(buff, 0, 128);
        team_subs = team_subs->next;
    }
    return (all_sub_teams);
}

char *get_sub_users(command *cmd)
{
    char buff[128] = {0};
    char *all_sub_users = NULL;
    team_t *team = find_team(NULL, cmd->args[0]);
    user_t *user_subs = team->subs;
    unsigned int length = 0;

    for (int i = 0; user_subs != NULL; i++) {
        sprintf(buff, "user name: \"%s\" user uuid: \"%s\"\r\n",
            user_subs->user_name, user_subs->user_uuid);
        length += strlen(buff);
        all_sub_users = realloc(all_sub_users, length * sizeof(char));
        if (i == 0)
            memset(all_sub_users, 0, length * sizeof(char));
        strcat(all_sub_users, buff);
        memset(buff, 0, 128);
        user_subs = user_subs->next;
    }
    return (all_sub_users);
}