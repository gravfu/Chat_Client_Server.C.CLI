/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

void users_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    const user_t *all_users = get_users();

    if (contains_errors(fd, user_connex, cmd))
        return;
    while (all_users) {
        sprintf(rsp, "username: \"%s\" user_uuid: \"%s\"\r\n",
            all_users->user_name, all_users->user_uuid);
        send_all(fd, rsp, strlen(rsp));
        all_users = all_users->next;
    }
    // What if no users are present
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.\n", fd);
        return (1);
    }
    if (cmd->num_args != 0) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.\n", fd);
        return (1);
    }
    return (0);
}