/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_subs
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_sub(team_t *p_team, const char *s_name, const char *s_uuid);

static void alloc_sub(user_t **new_sub, const char *s_name,
    const char *s_uuid);

void load_subs(team_t *team, const char *team_dir)
{
    char sub_info_path[4096] = {0};
    char s_name[MAX_NAME_LENGTH + 1] = {0};
    char s_uuid[37] = {0};
    const char *format = "name: \"%[^\"]\" uuid: \"%[^\"]\"\n";
    FILE *sub_info = NULL;

    if (!team || !team_dir) return;
    sprintf(sub_info_path, "%s%s", team_dir, "sub_info");
    sub_info = fopen(sub_info_path, "r");
    if (sub_info) {
        while (fscanf(sub_info, format, s_name, s_uuid) == 2) {
            add_sub(team, s_name, s_uuid);
            memset(s_name, 0, MAX_NAME_LENGTH);
            memset(s_uuid, 0, UUID_STR_LEN);
        }
        fclose(sub_info);
    }
}

void add_sub(team_t *p_team, const char *s_name, const char *s_uuid)
{
    user_t *list_cpy = p_team->subs;
    user_t *new_sub = NULL;

    if (list_cpy == NULL)
        alloc_sub(&(p_team->subs), s_name, s_uuid);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_sub(&new_sub, s_name, s_uuid);
        list_cpy->next = new_sub;
    }
}

static void alloc_sub(user_t **new_sub, const char *s_name,
    const char *s_uuid)
{
    if ((*new_sub = malloc(sizeof(user_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_sub)->user_name, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_sub)->user_name, s_name);
    memset((*new_sub)->user_uuid, 0, UUID_STR_LEN);
    strcpy((*new_sub)->user_uuid, s_uuid);
    (*new_sub)->next = NULL;
}

user_t *find_sub(user_t *sub_list, const char *sub_name, const char *sub_uuid)
{
    while (sub_list != NULL) {
        if (sub_name && strcmp(sub_name, sub_list->user_name) == 0) {
            return (sub_list);
        } else if (sub_uuid && strcmp(sub_uuid, sub_list->user_uuid) == 0) {
            return (sub_list);
        }
        sub_list = sub_list->next;
    }
    return (NULL);
}

void del_sub(user_t **sub_list, const char *sub_name, const char *sub_uuid)
{
    user_t *prev = NULL;
    user_t *temp = *sub_list;

    if (temp != NULL && strcmp(temp->user_name, sub_name) == 0 &&
        strcmp(temp->user_uuid, sub_uuid) == 0) {
        *sub_list = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->user_name, sub_name) != 0 &&
        strcmp(temp->user_uuid, sub_uuid) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}