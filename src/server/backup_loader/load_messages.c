/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** load_messages
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void add_chat(chat_t **chat_list, const char *chat_ref);

static void alloc_chat(chat_t **new_chat, const char *chat_ref);

void load_messages(chat_t **chat_list, const char *user_dir)
{
    char chat_info_path[4096] = {0};
    char chat_ref[42] = {0};
    const char *format = "ref: \"%s\"";
    FILE *chat_info = NULL;

    if (!chat_list || !user_dir) return;
    sprintf(chat_info_path, "%s%s", user_dir, "/chat_info");
    chat_info = fopen(chat_info_path, "r");
    if (chat_info) {
        while (fscanf(chat_info, format, chat_ref) == 1) {
            add_chat(chat_list, chat_ref);
            memset(chat_ref, 0, MAX_NAME_LENGTH);
        }
        fclose(chat_info);
    }
}
static void add_chat(chat_t **chat_list, const char *chat_ref)
{
    chat_t *list_cpy = *chat_list;
    chat_t *new_chat = NULL;

    if (*chat_list == NULL)
        alloc_chat(chat_list, chat_ref);
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        alloc_chat(&new_chat, chat_ref);
        list_cpy->next = new_chat;
    }
}

static void alloc_chat(chat_t **new_chat, const char *chat_ref)
{
    if ((*new_chat = malloc(sizeof(chat_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        return;
    }
    memset((*new_chat)->chat_ref, 0, MAX_NAME_LENGTH + 1);
    strcpy((*new_chat)->chat_ref, chat_ref);
    (*new_chat)->next = NULL;
}