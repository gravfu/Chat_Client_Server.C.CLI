/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_channels
*/

#include "load_channel.h"
#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void alloc_chann(channel_t **new_channel, const char *c_name,
    const char *c_uuid, const char *c_desc);

void load_channels(team_t *team, const char *team_dir)
{
    char c_info_path[4096] = {0};
    char c_name[MAX_NAME_LENGTH + 1] = {0};
    char c_uuid[UUID_STR_LEN] = {0};
    char c_desc[MAX_DESCRIPTION_LENGTH + 1] = {0};
    const char *format = "name: \"%[^\"]\" uuid: \"%[^\"]\" "
        "desc: \"%[^\"]\"\n";
    FILE *channel_info = NULL;

    if (!team || !team_dir) return;
    sprintf(c_info_path, "%s%s", team_dir, "channels/channel_info");
    parent_dir = team_dir;
    channel_info = fopen(c_info_path, "r");
    if (channel_info) {
        while (fscanf(channel_info, format, c_name, c_uuid, c_desc) == 3) {
            add_chann(team, c_name, c_uuid, c_desc);
            memset(c_name, 0, MAX_NAME_LENGTH);
            memset(c_uuid, 0, UUID_STR_LEN);
            memset(c_desc, 0, MAX_DESCRIPTION_LENGTH);
        }
        fclose(channel_info);
    }
}

void add_chann(team_t *p_team, const char *c_name, const char *c_uuid,
    const char *c_desc)
{
    channel_t *list_cpy = p_team->channels;
    channel_t *new_channel = NULL;

    if (list_cpy == NULL) {
        alloc_chann(&(p_team->channels), c_name, c_uuid, c_desc);
        p_team->channels->p_team = p_team;
    } else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_chann(&new_channel, c_name, c_uuid, c_desc);
        list_cpy->p_team = p_team;
        list_cpy->next = new_channel;
    }
}

static void alloc_chann(channel_t **new_channel, const char *c_name,
    const char *c_uuid, const char *c_desc)
{
    char channel_dir[4096] = {0};

    if ((*new_channel = malloc(sizeof(channel_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_channel)->channel_name, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_channel)->channel_name, c_name);
    memset((*new_channel)->channel_uuid, 0, UUID_STR_LEN);
    strcpy((*new_channel)->channel_uuid, c_uuid);
    memset((*new_channel)->channel_desc, 0, MAX_DESCRIPTION_LENGTH + 1);
    strcpy((*new_channel)->channel_desc, c_desc);
    sprintf(channel_dir, "%schannels/chan_%s/", parent_dir, c_uuid);
    (*new_channel)->threads = NULL;
    load_threads(*new_channel, channel_dir);
    (*new_channel)->next = NULL;
}

channel_t *find_channel(channel_t *channel_list, const char *channel_name,
    const char *channel_uuid)
{
    while (channel_list != NULL) {
        if (channel_name &&
            strcmp(channel_name, channel_list->channel_name) == 0) {
            return (channel_list);
        } else if (channel_uuid &&
            strcmp(channel_uuid, channel_list->channel_uuid) == 0) {
            return (channel_list);
        }
        channel_list = channel_list->next;
    }
    return (NULL);
}