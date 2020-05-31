/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** list_resources
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void get_threads_str_helper(char *buff, char *thread_body);

char *get_teams_str(void)
{
    char buff[128] = {0};
    char *teams_str = NULL;
    const team_t *teams = get_teams();
    int length = 0;

    for (int i = 0; teams != NULL; i++) {
        sprintf(buff, "teamname: \"%s\" teamuuid: \"%s\" teamdesc: \"%s\"\r\n",
            teams->team_name, teams->team_uuid, teams->team_desc);
        length += strlen(buff);
        teams_str = realloc(teams_str, (length + 1) * sizeof(char));
        if (i == 0)
            memset(teams_str, 0, (length + 1) * sizeof(char));
        strcat(teams_str, buff);
        memset(buff, 0, 128);
        teams = teams->next;
    }
    return (teams_str);
}

char *get_channels_str(connex_t *user_connex)
{
    char buff[128] = {0};
    char *channels_str = NULL;
    const channel_t *channels = ((team_t *)(user_connex->context))->channels;
    unsigned int length = 0;

    for (int i = 0; channels != NULL; i++) {
        sprintf(buff, "channelname: \"%s\" channeluuid: \"%s\" "
            "channeldesc: \"%s\"\r\n", channels->channel_name,
            channels->channel_uuid, channels->channel_desc);
        length += strlen(buff);
        channels_str = realloc(channels_str, (length + 1) * sizeof(char));
        if (i == 0)
            memset(channels_str, 0, (length + 1) * sizeof(char));
        strcat(channels_str, buff);
        memset(buff, 0, 128);
        channels = channels->next;
    }
    return (channels_str);
}

char *get_threads_str(connex_t *user_connex)
{
    char buff[1024] = {0};
    char *threads_str = NULL;
    const thread_t *threads = ((channel_t *)(user_connex->context))->threads;
    unsigned int length = 0;

    for (int i = 0; threads != NULL; i++) {
        sprintf(buff, "threaduuid: \"%s\" useruuid: \"%s\" time: \"%s\" "
            "threadtitle: \"%s\" body: (%s)\r\n", threads->thread_uuid,
            threads->user_uuid, threads->timestamp, threads->thread_title,
            threads->thread_init);
        length += strlen(buff);
        threads_str = realloc(threads_str, (length + 1) * sizeof(char));
        if (i == 0) memset(threads_str, 0, (length + 1) * sizeof(char));
        strcat(threads_str, buff);
        memset(buff, 0, 1024 * sizeof(char));
        threads = threads->next;
    }
    return (threads_str);
}