/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_team_subs
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void alloc_team_sub(team_t **new_team_sub, const char *t_name,
    const char *t_uuid, const char *t_desc);

void load_team_subs(user_t *user, const char *user_dir)
{
    char sub_info_path[4096] = {0};
    char t_name[MAX_NAME_LENGTH + 1] = {0};
    char t_uuid[UUID_STR_LEN] = {0};
    char t_desc[MAX_DESCRIPTION_LENGTH + 1] = {0};
    const char *format = "name: \"%[^\"]\" uuid: \"%[^\"]\" "
        "desc: \"%[^\"]\"\n";
    FILE *sub_info = NULL;

    if (!user || !user_dir) return;
    sprintf(sub_info_path, "%s%s", user_dir, "team_sub_info");
    sub_info = fopen(sub_info_path, "r");
    if (sub_info) {
        while (fscanf(sub_info, format, t_name, t_uuid, t_desc) == 3) {
            add_team_sub(user, t_name, t_uuid, t_desc);
            memset(t_name, 0, MAX_NAME_LENGTH);
            memset(t_uuid, 0, UUID_STR_LEN);
            memset(t_desc, 0, MAX_DESCRIPTION_LENGTH);
        }
        fclose(sub_info);
    }
}

void add_team_sub(user_t *p_user, const char *t_name, const char *t_uuid,
    const char *t_desc)
{
    team_t *list_cpy = p_user->team_subs;
    team_t *new_team_sub = NULL;

    if (list_cpy == NULL)
        alloc_team_sub(&(p_user->team_subs), t_name, t_uuid, t_desc);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_team_sub(&new_team_sub, t_name, t_uuid, t_desc);
        list_cpy->next = new_team_sub;
    }
}

static void alloc_team_sub(team_t **new_team_sub, const char *t_name,
    const char *t_uuid, const char *t_desc)
{
    if ((*new_team_sub = malloc(sizeof(team_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_team_sub)->team_name, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_team_sub)->team_name, t_name);
    memset((*new_team_sub)->team_uuid, 0, UUID_STR_LEN);
    strcpy((*new_team_sub)->team_uuid, t_uuid);
    memset((*new_team_sub)->team_desc, 0, MAX_DESCRIPTION_LENGTH + 1);
    strcpy((*new_team_sub)->team_desc, t_desc);
    (*new_team_sub)->subs = NULL;
    (*new_team_sub)->channels = NULL;
    (*new_team_sub)->next = NULL;
}

team_t *find_team_sub(team_t *sub_list, const char *t_name,
    const char *t_uuid)
{
    while (sub_list != NULL) {
        if (t_name && strcmp(t_name, sub_list->team_name) == 0) {
            return (sub_list);
        } else if (t_uuid && strcmp(t_uuid, sub_list->team_uuid) == 0) {
            return (sub_list);
        }
        sub_list = sub_list->next;
    }
    return (NULL);
}

void del_team_sub(team_t **sub_list, const char *t_name, const char *t_uuid)
{
    team_t *prev = NULL;
    team_t *temp = *sub_list;

    if (temp != NULL && strcmp(temp->team_name, t_name) == 0 &&
        strcmp(temp->team_uuid, t_uuid) == 0) {
        *sub_list = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->team_name, t_name) != 0 &&
        strcmp(temp->team_uuid, t_uuid) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}