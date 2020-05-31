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

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

void user_cmd(int fd, command_t *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    const user_t *found_user = NULL;
    int status = 0;

    if (contains_errors(fd, user_connex, cmd))
        return;
    found_user = find_user(NULL, cmd->args[0]);
    status = is_connected(found_user);
    sprintf(rsp, "START_RSP\r\n%d\r\nusername: \"%s\" useruuid: \"%s\" "
        "status: \"%d\"\r\nEND_RSP\r\n", RSP_USER, found_user->user_name,
        found_user->user_uuid, status);
    send_direct(user_connex->sock_fd, rsp);
}

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd)
{
    const user_t *found_user = NULL;

    if (!user_connex->user || !user_connex->logged_in) {
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
    if (!user_exist(user_connex, cmd))
        return (1);
    return (0);
}