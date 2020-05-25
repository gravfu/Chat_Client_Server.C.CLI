/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_users
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

static void alloc_user(user_t **new_user, const char *u_name,
    const char *u_uuid);

void add_user(const char *u_name, const char *u_uuid);

void load_users()
{
    char u_name[MAX_NAME_LENGTH + 1] = {0};
    char u_uuid[37] = {0};
    const char *format = "name: \"%[^\"]\" uuid: \"%[^\"]\"\n";
    FILE *user_info = NULL;

    user_info = fopen("./backup/users/user_info", "r");
    if (user_info) {
        while (fscanf(user_info, format, u_name, u_uuid) == 2) {
            add_user(u_name, u_uuid);
            memset(u_name, 0, MAX_NAME_LENGTH);
            memset(u_uuid, 0, 36);
        }
        fclose(user_info);
    }
}

void add_user(const char *u_name, const char *u_uuid)
{
    user_t *list_cpy = user_list;
    user_t *new_user = NULL;

    if (user_list == NULL)
        alloc_user(&user_list, u_name, u_uuid);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_user(&new_user, u_name, u_uuid);
        list_cpy->next = new_user;
    }
}

static void alloc_user(user_t **new_user, const char *u_name,
    const char *u_uuid)
{
    if ((*new_user = malloc(sizeof(user_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_user)->user_name, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_user)->user_name, u_name);
    memset((*new_user)->user_uuid, 0, UUID_LENGTH + 1);
    strcpy((*new_user)->user_uuid, u_uuid);
    (*new_user)->next = NULL;
}

user_t *find_user(const char *user_name, const char *user_uuid)
{
    user_t *list_cpy = user_list;

    while (list_cpy != NULL) {
        if (user_name && strcmp(user_name, list_cpy->user_name) == 0) {
            return (list_cpy);
        } else if (user_uuid && strcmp(user_uuid, list_cpy->user_uuid) == 0) {
            return (list_cpy);
        }
        list_cpy = list_cpy->next;
    }
    return (NULL);
}

const user_t *get_users()
{
    return (user_list);
}