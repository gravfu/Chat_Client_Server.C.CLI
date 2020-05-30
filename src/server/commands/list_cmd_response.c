/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_cmd_response
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void list_comments_response(connex_t *user_connex, const char *comments)
{
    char *rsp = NULL;
    int len_str = (comments != NULL) ? strlen(comments) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_COMMENT,
        comments);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}

void list_threads_response(connex_t *user_connex, const char *threads)
{
    char *rsp = NULL;
    int len_str = (threads != NULL) ? strlen(threads) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_THREAD,
        threads);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}

void list_channels_response(connex_t *user_connex, const char *channels)
{
    char *rsp = NULL;
    int len_str = (channels != NULL) ? strlen(channels) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_CHANNEL,
        channels);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}

void list_teams_response(connex_t *user_connex, const char *teams)
{
    char *rsp = NULL;
    int len_str = (teams != NULL) ? strlen(teams) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_TEAM,
        teams);
    send_direct(user_connex->sock_fd, rsp);
    free(rsp);
}