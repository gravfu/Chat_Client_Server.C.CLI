/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** drop_sub
*/

#include "my_teams_srv.h"
#include <stdio.h>
#include <string.h>

static void drop_sub_helper(FILE *sub_info, FILE *sub_info_tmp,
    const char *sub_name, const char *sub_uuid);

int drop_sub(team_t *team, const char *sub_name, const char *sub_uuid)
{
    const char *info_format = "./backup/teams/team_%s/sub_info";
    const char *tmp_format = "./backup/teams/team_%s/sub_info_tmp";
    char sub_info_path[4096] = {0};
    char sub_info_tmp_path[4096] = {0};
    FILE *sub_info = NULL;
    FILE *sub_info_tmp = NULL;

    sprintf(sub_info_path, info_format, team->team_uuid);
    sprintf(sub_info_tmp_path, tmp_format, team->team_uuid);
    sub_info = fopen(sub_info_path, "r");
    sub_info_tmp = fopen(sub_info_tmp_path, "w+");
    if (sub_info && sub_info_tmp) {
        drop_sub_helper(sub_info, sub_info_tmp, sub_name, sub_uuid);
        fclose(sub_info);
        fclose(sub_info_tmp);
        remove(sub_info_path);
        rename(sub_info_tmp_path, sub_info_path);
    }
}

static void drop_sub_helper(FILE *sub_info, FILE *sub_info_tmp,
    const char *sub_name, const char *sub_uuid)
{
    char s_name[MAX_NAME_LENGTH + 1] = {0};
    char s_uuid[UUID_STR_LEN] = {0};
    const char *sub_format = "name: \"%[^\"]\" uuid: \"%[^\"]\"\n";

    while (fscanf(sub_info, sub_format, s_name, s_uuid) == 2) {
        if (strcmp(s_name, sub_name) != 0 && strcmp(s_uuid, sub_uuid) != 0) {
            fprintf(sub_info_tmp, "name: \"%s\" uuid: \"%s\"\n", s_name,
                s_uuid);
        }
        memset(s_name, 0, MAX_NAME_LENGTH);
        memset(s_uuid, 0, UUID_STR_LEN);
    }
}

int drop_team_sub(user_t *user, const char *t_name, const char *t_uuid)
{
    const char *info_format = "./backup/users/usr_%s/team_sub_info";
    const char *tmp_format = "./backup/users/usr_%s/team_sub_info_tmp";
    char sub_info_path[4096] = {0};
    char sub_info_tmp_path[4096] = {0};
    FILE *sub_info = NULL;
    FILE *sub_info_tmp = NULL;

    sprintf(sub_info_path, info_format, user->user_uuid);
    sprintf(sub_info_tmp_path, tmp_format, user->user_uuid);
    sub_info = fopen(sub_info_path, "r");
    sub_info_tmp = fopen(sub_info_tmp_path, "w+");
    if (sub_info && sub_info_tmp) {
        drop_sub_helper(sub_info, sub_info_tmp, t_name, t_uuid);
        fclose(sub_info);
        fclose(sub_info_tmp);
        remove(sub_info_path);
        rename(sub_info_tmp_path, sub_info_path);
    }
}

static void drop_team_sub_helper(FILE *sub_info, FILE *sub_info_tmp,
    const char *t_name, const char *t_uuid)
{
    char s_name[MAX_NAME_LENGTH + 1] = {0};
    char s_uuid[UUID_STR_LEN] = {0};
    char s_desc[MAX_DESCRIPTION_LENGTH + 1] = {0};
    const char *sub_format = "name: \"%[^\"]\" uuid: \"%[^\"]\""
        " desc: \"%[^\"]\"\n";

    while (fscanf(sub_info, sub_format, s_name, s_uuid) == 2) {
        if (strcmp(s_name, t_name) != 0 && strcmp(s_uuid, t_uuid) != 0) {
            fprintf(sub_info_tmp, "name: \"%s\" uuid: \"%s\" desc: \"%s\"\n",
                s_name, s_uuid);
        }
        memset(s_name, 0, MAX_NAME_LENGTH);
        memset(s_uuid, 0, UUID_STR_LEN);
        memset(s_desc, 0, MAX_DESCRIPTION_LENGTH);
    }
}