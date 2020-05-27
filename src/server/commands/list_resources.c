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

char *get_teams_str()
{
    char buff[128] = {0};
    char *teams_str = NULL;
    const team_t *teams = get_teams();
    unsigned int length = 0;

    for (int i = 0; teams != NULL; i++) {
        sprintf(buff, "\tteam name: \"%s\" team uuid: \"%s\"\r\n",
            teams->team_name, teams->team_uuid);
        length += strlen(buff);
        teams_str = realloc(teams_str, length * sizeof(char));
        if (i == 0)
            memset(teams_str, 0, length * sizeof(char));
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
        sprintf(buff, "\tchannel name: \"%s\" channel uuid: \"%s\"\r\n",
            channels->channel_name, channels->channel_uuid);
        length += strlen(buff);
        channels_str = realloc(channels_str, length * sizeof(char));
        if (i == 0)
            memset(channels_str, 0, length * sizeof(char));
        strcat(channels_str, buff);
        memset(buff, 0, 128);
        channels = channels->next;
    }
    return (channels_str);
}

char *get_threads_str(connex_t *user_connex)
{
    char buff[128] = {0};
    char *threads_str = NULL;
    const thread_t *threads = ((channel_t *)(user_connex->context))->threads;
    unsigned int length = 0;

    for (int i = 0; threads != NULL; i++) {
        sprintf(buff, "\tthread title name: \"%s\" thread uuid: \"%s\"\r\n",
            threads->thread_title, threads->thread_uuid);
        length += strlen(buff);
        threads_str = realloc(threads_str, length * sizeof(char));
        if (i == 0)
            memset(threads_str, 0, length * sizeof(char));
        strcat(threads_str, buff);
        memset(buff, 0, 128);
        threads = threads->next;
    }
    return (threads_str);
}

char *get_comments_str(connex_t *user_connex)
{
    char *comments_str = NULL;
    char thread_path[4096] = {0};
    FILE *thread_file = NULL;
    long fsize = 0;
    const thread_t *thread = (thread_t *)(user_connex->context);

    sprintf(thread_path, "./backup/teams/team_%s/channels/chan_%s/threads/"
        "thread_%s", thread->p_channel->p_team->team_uuid,
        thread->p_channel->channel_uuid, thread->thread_uuid);
    thread_file = fopen(thread_path, "r");
    fseek(thread_file, 0, SEEK_END);
    fsize = ftell(thread_file);
    fseek(thread_file, 0, SEEK_SET);
    comments_str = malloc(fsize + 1);
    fread(comments_str, 1, fsize, thread_file);
    fclose(thread_file);
    comments_str[fsize] = 0;
    return (comments_str);
}