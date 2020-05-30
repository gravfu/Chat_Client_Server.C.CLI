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

void list_comments_response(user_t *user, const char *comments)
{
    char *rsp = NULL;
    int len_str = (comments != NULL) ? strlen(comments) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_COMMENT,
        comments);
    add_notification(user, rsp);
    free(rsp);
}

void list_threads_response(user_t *user, const char *threads)
{
    char *rsp = NULL;
    int len_str = (threads != NULL) ? strlen(threads) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_THREAD,
        threads);
    add_notification(user, rsp);
    free(rsp);
}

void list_channels_response(user_t *user, const char *channels)
{
    char *rsp = NULL;
    int len_str = (channels != NULL) ? strlen(channels) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_CHANNEL,
        channels);
    add_notification(user, rsp);
    free(rsp);
}

void list_teams_response(user_t *user, const char *teams)
{
    char *rsp = NULL;
    int len_str = (teams != NULL) ? strlen(teams) : 0;
    int rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;

    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_LIST_TEAM,
        teams);
    add_notification(user, rsp);
    free(rsp);
}