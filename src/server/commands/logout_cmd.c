/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** logout_cmd
*/

#include "logging_server.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

void logout_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);

    if (contains_errors(fd, user_connex, cmd))
        return;
    server_event_user_logged_out(user_connex->user->user_uuid);
    sprintf(rsp, "START_RSP\r\n%d: Logout successful.\r\nEND_RSP\r\n",
        RSP_LOGOUT);
    send_all(fd, rsp, strlen(rsp));
    delete_conn(fd);
    close(fd);
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.", fd);
        return (1);
    }
    if (cmd->num_args != 0) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.", fd);
        return (1);
    }
    return (0);
}