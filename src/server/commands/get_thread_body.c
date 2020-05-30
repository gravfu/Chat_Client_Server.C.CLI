/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_thread_body
*/

#include "my_teams_srv.h"
#include <stdio.h>
#include <stdlib.h>

char *get_thread_body(const thread_t *thread)
{
    char thread_path[4096] = {0};
    char *thread_str = NULL;
    FILE *thread_file = NULL;
    long fsize = 0;

    sprintf(thread_path, "./backup/teams/team_%s/channels/chan_%s/threads"
        "/thread_%s", thread->p_channel->p_team->team_uuid,
        thread->p_channel->channel_uuid, thread->thread_uuid);
    printf("%s", thread_path);
    thread_file = fopen(thread_path, "r");
    fseek(thread_file, 0, SEEK_END);
    fsize = ftell(thread_file);
    fseek(thread_file, 0, SEEK_SET);
    thread_str = malloc((fsize + 1) * sizeof(char));
    fread(thread_str, sizeof(char), fsize, thread_file);
    fclose(thread_file);
    thread_str[fsize] = 0;
    return (thread_str);
}