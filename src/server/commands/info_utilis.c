/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** info_utilis
*/

#include "my_teams_srv.h"
#include <stddef.h>

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
    char *buff = NULL;
    char *threads_str = NULL;
    char *thread_body = NULL;
    const thread_t *threads = ((channel_t *)(user_connex->context))->threads;
    unsigned int length = 0;

    for (int i = 0; threads != NULL; i++) {
        thread_body = get_thread_body(threads);
        buff = malloc((strlen(thread_body) + 256) * sizeof(char));
        sprintf(buff, "threaduuid: \"%s\" useruuid: \"%s\" time: \"%s\" "
            "threadtitle: \"%s\" body: %s\r\n", threads->thread_uuid,
            threads->user_uuid, threads->timestamp, threads->thread_title,
            thread_body);
        length += strlen(buff);
        threads_str = realloc(threads_str, (length + 1) * sizeof(char));
        if (i == 0) memset(threads_str, 0, (length + 1) * sizeof(char));
        strcat(threads_str, buff);
        get_threads_str_helper(buff, thread_body);
        threads = threads->next;
    }
    return (threads_str);
}