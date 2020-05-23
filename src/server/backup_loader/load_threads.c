/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_threads
*/

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

void load_threads(channel_t *channel, const char *channel_dir)
{
    char t_info_path[4096] = {0};
    char t_title[MAX_NAME_LENGTH + 1] = {0};
    char t_uuid[37] = {0};
    char t_init[MAX_BODY_LENGTH + 1] = {0};
    const char *format = "title: \"%s\" uuid: \"%s\" init: \"%s\"";
    FILE *thread_info = NULL;

    if (!channel || !channel_dir) return;
    strcpy(t_info_path, channel_dir);
    strcpy(t_info_path, "threads/thread_info");
    thread_info = fopen(t_info_path, "r");
    if (thread_info) {
        while (fscanf(thread_info, format, t_title, t_uuid, t_init) == 3) {
            add_thread(&(channel->threads), t_title, t_uuid, t_init);
            // add code to read threads
        }
    }
}

static void add_thread(thread_t **thread_list, const char *t_title,
    const char *t_uuid, const char *t_init)
{
    thread_t *list_cpy = *thread_list;
    thread_t *new_thread = NULL;

    if (*thread_list == NULL)
        alloc_thread(thread_list, t_title, t_uuid, t_init);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_thread(&new_thread, t_title, t_uuid, t_init);
        list_cpy->next = new_thread;
    }
}

static void alloc_thread(thread_t **new_thread, const char *t_title,
    const char *t_uuid, const char *t_init)
{
    if ((*new_thread = malloc(sizeof(thread_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_thread)->thread_title, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_thread)->thread_title, t_title);
    if (uuid_parse(t_uuid, (*new_thread)->thread_uuid) == -1) {
        free(*new_thread);
        *new_thread = NULL;
        printf("Error parsing uuid. Send error to lib\n");
        return;
    }
    memset((*new_thread)->thread_init, 0, MAX_BODY_LENGTH + 1);
    strcpy((*new_thread)->thread_init, t_init);
    (*new_thread)->next = NULL;
}