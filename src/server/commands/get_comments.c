/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_comments
*/

#include "my_teams_srv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_comments(FILE *thread_file, const thread_t *thread);

static void init_str(int iteration, char *str, int len_str);

char *get_comments_str(connex_t *user_connex)
{
    char *comments_str = NULL;
    char thread_path[4096] = {0};
    FILE *thread_file = NULL;
    const thread_t *thread = (thread_t *)(user_connex->context);
    int i = 0;

    sprintf(thread_path, "./backup/teams/team_%s/channels/chan_%s/threads/"
        "thread_%s", thread->p_channel->p_team->team_uuid,
        thread->p_channel->channel_uuid, thread->thread_uuid);
    thread_file = fopen(thread_path, "r");
    if (thread_file) {
        comments_str = read_comments(thread_file, thread);
        fclose(thread_file);
    }
    return (comments_str);
}

static char *read_comments(FILE *thread_file, const thread_t *thread)
{
    char buff[1024] = {0};
    char cmt_body[MAX_BODY_LENGTH + 1] = {0};
    char *comments_str = NULL;
    const char *format = "%[^:]: %[^:]: %[^\r\n\n]\r\n\n";
    char time_str[TIME_LEN] = {0};
    char u_uuid[UUID_STR_LEN] = {0};
    int i = 0;
    int length = 0;

    while (fscanf(thread_file, format, u_uuid, cmt_body, time_str) == 3) {
        sprintf(buff, "threaduuid: \"%s\" useruuid: \"%s\" time: \"%s\" "
            "body: %s\r\n", thread->thread_uuid, u_uuid, time_str,
            cmt_body);
        length += strlen(buff);
        comments_str = realloc(comments_str, (length + 1) * sizeof(char));
        init_str(i++, comments_str, length + 1);
        strcat(comments_str, buff);
        memset(buff, 0, 1024);
    }
    return (comments_str);
}

static void init_str(int iteration, char *str, int len_str)
{
    if (iteration == 0)
        memset(str, 0, len_str * sizeof(char));
}