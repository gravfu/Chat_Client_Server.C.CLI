/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_threads
*/

#include "my_teams_srv.h"
#include "load_thread.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_thread(channel_t *p_channel, const char *t_title,
    const char *t_uuid, const char *t_init);

static void alloc_thread(thread_t **new_thread, const char *t_title,
    const char *t_uuid, const char *t_init);

void load_threads(channel_t *channel, const char *channel_dir)
{
    char t_info_path[4096] = {0};
    char t_title[MAX_NAME_LENGTH + 1] = {0};
    char t_uuid[37] = {0};
    char t_init[MAX_BODY_LENGTH + 1] = {0};
    const char *format = "title: \"%[^\"]\" uuid: \"%[^\"]\" init: \"%[^\"]\"";
    FILE *thread_info = NULL;

    if (!channel || !channel_dir) return;
    sprintf(t_info_path, "%s%s", channel_dir, "threads/thread_info");
    parent_dir = channel_dir;
    thread_info = fopen(t_info_path, "r");
    if (thread_info) {
        while (fscanf(thread_info, format, t_title, t_uuid, t_init) == 3) {
            add_thread(channel, t_title, t_uuid, t_init);
            memset(t_title, 0, MAX_NAME_LENGTH);
            memset(t_uuid, 0, UUID_STR_LEN);
            memset(t_init, 0, MAX_BODY_LENGTH);
        }
        fclose(thread_info);
    }
}

void add_thread(channel_t *p_channel, const char *t_title,
    const char *t_uuid, const char *t_init)
{
    thread_t *list_cpy = p_channel->threads;
    thread_t *new_thread = NULL;

    if (list_cpy == NULL) {
        alloc_thread(&(p_channel->threads), t_title, t_uuid, t_init);
        p_channel->threads->p_channel = p_channel;
    } else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_thread(&new_thread, t_title, t_uuid, t_init);
        list_cpy->p_channel = p_channel;
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
    memset((*new_thread)->thread_uuid, 0, UUID_STR_LEN);
    strcpy((*new_thread)->thread_uuid, t_uuid);
    memset((*new_thread)->thread_init, 0, MAX_BODY_LENGTH + 1);
    strcpy((*new_thread)->thread_init, t_init);
    (*new_thread)->next = NULL;
}

thread_t *find_thread(thread_t *thread_list, const char *thread_title,
    const char *thread_uuid)
{
    while (thread_list != NULL) {
        if (thread_title &&
            strcmp(thread_title, thread_list->thread_title) == 0) {
            return (thread_list);
        } else if (thread_uuid &&
            strcmp(thread_uuid, thread_list->thread_uuid) == 0) {
            return (thread_list);
        }
        thread_list = thread_list->next;
    }
    return (NULL);
}