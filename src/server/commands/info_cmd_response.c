/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info_cmd_response
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void info_thread_response(connex_t *user_connex, const char *thread)
{
    char *rsp = NULL;
    int len_str = (thread != NULL) ? strlen(thread) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_INFO_THREAD,
        thread);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}

void info_channel_response(connex_t *user_connex, const char *channel)
{
    char *rsp = NULL;
    int len_str = (channel != NULL) ? strlen(channel) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_INFO_CHANNEL,
        channel);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}

void info_team_response(connex_t *user_connex, const char *team)
{
    char *rsp = NULL;
    int len_str = (team != NULL) ? strlen(team) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_INFO_TEAM,
        team);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}

void info_user_response(connex_t *user_connex, const char *user)
{
    char *rsp = NULL;
    int len_str = (user != NULL) ? strlen(user) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_INFO_USER,
        user);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}