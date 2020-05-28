/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** user_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

void user_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    const user_t *found_user = NULL;

    if (contains_errors(fd, user_connex, cmd))
        return;
    found_user = find_user(NULL, cmd->args[0]);
    sprintf(rsp, "START_RSP\r\n%d\r\nusername: \"%s\" useruuid: \"%s\"\r\n"
        "END_RSP\r\n", RSP_USER, found_user->user_name, found_user->user_uuid);
    send_all(fd, rsp, strlen(rsp));
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    const user_t *found_user = NULL;

    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.", fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, "Missing parameters.", fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.", fd);
        return (1);
    }
    found_user = find_user(NULL, cmd->args[0]);
    if (!found_user) {
        send_error(ERR_NOSUCHUSER, "Invalid uuid.", fd);
        return (1);
    }
    return (0);
}