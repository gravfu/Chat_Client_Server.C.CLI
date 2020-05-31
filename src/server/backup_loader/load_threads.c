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
#include <time.h>

static void alloc_thread(thread_t **new_thread, channel_t *p_channel,
    thread_t *to_copy);

static void add_loaded_thread(channel_t *p_channel);

void load_threads(channel_t *channel, const char *channel_dir)
{
    char t_info_path[4096] = {0};
    const char *format = "u_uuid: \"%[^\"]\" title: \"%[^\"]\" "
        "uuid: \"%[^\"]\" init: \"%[^\"]\" time: \"%[^\"]\"\n";
    FILE *thread_info = NULL;

    if (!channel || !channel_dir) return;
    sprintf(t_info_path, "%s%s", channel_dir, "threads/thread_info");
    thread_info = fopen(t_info_path, "r");
    if (thread_info) {
        while (fscanf(thread_info, format, t_u_uuid, t_title, t_uuid, t_init,
            t_timestamp) == 5) {
            add_loaded_thread(channel);
        }
        fclose(thread_info);
    }
}

void add_thread(channel_t *p_channel, thread_t *to_copy)
{
    thread_t *list_cpy = p_channel->threads;
    thread_t *new_thread = NULL;

    if (list_cpy == NULL) {
        alloc_thread(&(p_channel->threads), p_channel, to_copy);
    } else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_thread(&new_thread, p_channel, to_copy);
        list_cpy->next = new_thread;
    }
}

static void alloc_thread(thread_t **new_thread, channel_t *p_channel,
    thread_t *to_copy)
{
    if ((*new_thread = malloc(sizeof(thread_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_thread)->thread_title, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_thread)->thread_title, to_copy->thread_title);
    memset((*new_thread)->thread_uuid, 0, UUID_STR_LEN);
    strcpy((*new_thread)->thread_uuid, to_copy->thread_uuid);
    memset((*new_thread)->thread_init, 0, MAX_BODY_LENGTH + 1);
    strcpy((*new_thread)->thread_init, to_copy->thread_init);
    memset((*new_thread)->timestamp, 0, TIME_LEN);
    strcpy((*new_thread)->timestamp, to_copy->timestamp);
    memset((*new_thread)->user_uuid, 0, UUID_STR_LEN);
    strcpy((*new_thread)->user_uuid, to_copy->user_uuid);
    (*new_thread)->p_channel = p_channel;
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

static void add_loaded_thread(channel_t *p_channel)
{
    thread_t new_thread;

    memset(new_thread.thread_title, 0, MAX_NAME_LENGTH + 1);
    strcpy(new_thread.thread_title, t_title);
    strcpy(new_thread.thread_uuid, t_uuid);
    memset(new_thread.thread_init, 0, MAX_BODY_LENGTH + 1);
    strcpy(new_thread.thread_init, t_init);
    strcpy(new_thread.timestamp, t_timestamp);
    strcpy(new_thread.user_uuid, t_u_uuid);
    new_thread.p_channel = p_channel;
    add_thread(p_channel, &new_thread);
}