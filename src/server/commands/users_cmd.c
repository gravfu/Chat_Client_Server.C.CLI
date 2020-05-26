/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** users_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static char *get_users_str();

void users_cmd(int fd, command *cmd)
{
    char *rsp = NULL;
    char *user_str = NULL;
    connex_t *user_connex = find_connex(fd);
    const user_t *all_users = get_users();
    unsigned int len_str = 0;
    unsigned int rsp_len = 0;

    if (contains_errors(fd, user_connex, cmd))
        return;
    user_str = get_users_str();
    len_str = (user_str != NULL) ? strlen(user_str) : len_str;
    rsp_len = strlen("START_RSP\r\n") + strlen("000: Subscribed to:\r\n") +
        len_str + strlen("END_RSP\r\n");
    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d: Users in domain:\r\n%sEND_RSP\r\n",
        RSP_USERS, user_str);
    if (user_str) free(user_str);
    send_all(fd, rsp, strlen(rsp));
    free(rsp);
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

static char *get_users_str()
{
    char buff[128] = {0};
    char *users_str = NULL;
    const user_t *users = get_users();
    unsigned int length = 0;

    for (int i = 0; users != NULL; i++) {
        sprintf(buff, "\tuser name: \"%s\" user uuid: \"%s\"\r\n",
            users->user_name, users->user_uuid);
        length += strlen(buff);
        users_str = realloc(users_str, length * sizeof(char));
        if (i == 0)
            memset(users_str, 0, length * sizeof(char));
        strcat(users_str, buff);
        memset(buff, 0, 128);
        users = users->next;
    }
    return (users_str);
}