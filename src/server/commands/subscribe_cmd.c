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

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

void subscribe_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);

    if (contains_errors(fd, user_connex, cmd))
        return;
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    team_t *team = NULL;

    if (!user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.\n", fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, "Missing paramters.\n", fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.\n", fd);
        return (1);
    }
    team = find_team(NULL, cmd->args[0]);
    if (!team) {
        send_error(ERR_NOSUCHTEAM, "No such team exists.\n", fd);
        return (1);
    }
    return (0);
}

void subscribe()
{
    char file_path[4096];
    const char *format = "./backup/teams/team_%s/sub_info";
    FILE *thread_file = NULL;
}