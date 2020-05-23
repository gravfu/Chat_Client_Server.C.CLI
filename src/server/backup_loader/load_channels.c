/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_channels
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

void load_channels(team_t *team, const char *team_dir)
{
    char c_info_path[4096] = {0};
    char c_name[MAX_NAME_LENGTH + 1] = {0};
    char c_uuid[37] = {0};
    char c_desc[MAX_DESCRIPTION_LENGTH + 1] = {0};
    const char *format = "name: \"%s\" uuid: \"%s\" desc: \"%s\"";
    FILE *channel_info = NULL;

    if (!team || !team_dir) return;
    strcpy(c_info_path, team_dir);
    strcpy(c_info_path, "channels/channel_info");
    channel_info = fopen(c_info_path, "r");
    if (channel_info) {
        while (fscanf(channel_info, format, c_name, c_uuid, c_desc) == 3) {
            add_chann(&(team->channels), c_name, c_uuid, c_desc);
            // add code to read threads
        }
    }
}

void add_chann(channel_t **chann_list, const char *c_name, const char *c_uuid,
    const char *c_desc)
{
    channel_t *list_cpy = *chann_list;
    channel_t *new_channel = NULL;

    if (*chann_list == NULL)
        alloc_chann(chann_list, c_name, c_uuid, c_desc);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_chann(&new_channel, c_name, c_uuid, c_desc);
        list_cpy->next = new_channel;
    }
}

static void alloc_chann(channel_t **new_channel, const char *c_name,
    const char *c_uuid, const char *c_desc)
{
    if ((*new_channel = malloc(sizeof(channel_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_channel)->channel_name, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_channel)->channel_name, c_name);
    if (uuid_parse(c_uuid, (*new_channel)->channel_uuid) == -1) {
        free(*new_channel);
        *new_channel = NULL;
        printf("Error parsing uuid. Send error to lib\n");
        return;
    }
    memset((*new_channel)->channel_desc, 0, MAX_DESCRIPTION_LENGTH + 1);
    strcpy((*new_channel)->channel_desc, c_desc);
    (*new_channel)->threads = NULL;
    // load threads here
    (*new_channel)->next = NULL;
}