/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_teams
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void alloc_team(team_t **new_team, const char *t_name,
    const char *t_uuid, const char *t_desc);

void load_teams()
{
    char t_name[MAX_NAME_LENGTH + 1] = {0};
    char t_uuid[UUID_STR_LEN] = {0};
    char t_desc[MAX_DESCRIPTION_LENGTH + 1] = {0};
    const char *format = "name: \"%[^\"]\" uuid: \"%[^\"]\" desc: \"%[^\"]\"\n";
    FILE *team_info = NULL;

    team_info = fopen("./backup/teams/team_info", "r");
    if (team_info) {
        while (fscanf(team_info, format, t_name, t_uuid, t_desc) == 3) {
            add_team(t_name, t_uuid, t_desc);
            memset(t_name, 0, MAX_NAME_LENGTH);
            memset(t_uuid, 0, UUID_STR_LEN);
            memset(t_desc, 0, MAX_DESCRIPTION_LENGTH);
        }
        fclose(team_info);
    }
}

void add_team(const char *c_name, const char *c_uuid, const char *c_desc)
{
    team_t *list_cpy = team_list;
    team_t *new_team = NULL;

    if (team_list == NULL)
        alloc_team(&team_list, c_name, c_uuid, c_desc);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_team(&new_team, c_name, c_uuid, c_desc);
        list_cpy->next = new_team;
    }
}

static void alloc_team(team_t **new_team, const char *t_name,
    const char *t_uuid, const char *t_desc)
{
    char team_dir[4096] = {0};

    if ((*new_team = malloc(sizeof(team_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_team)->team_name, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_team)->team_name, t_name);
    memset((*new_team)->team_uuid, 0, UUID_STR_LEN);
    strcpy((*new_team)->team_uuid, t_uuid);
    memset((*new_team)->team_desc, 0, MAX_DESCRIPTION_LENGTH + 1);
    strcpy((*new_team)->team_desc, t_desc);
    sprintf(team_dir, "./backup/teams/team_%s/", t_uuid);
    (*new_team)->subs = NULL;
    load_subs(*new_team, team_dir);
    (*new_team)->channels = NULL;
    load_channels(*new_team, team_dir);
    (*new_team)->next = NULL;
}

team_t *find_team(const char *team_name, const char *team_uuid)
{
    team_t *list_cpy = team_list;

    while (list_cpy != NULL) {
        if (team_name && strcmp(team_name, list_cpy->team_name) == 0) {
            return (list_cpy);
        } else if (team_uuid && strcmp(team_uuid, list_cpy->team_uuid) == 0) {
            return (list_cpy);
        }
        list_cpy = list_cpy->next;
    }
    return (NULL);
}