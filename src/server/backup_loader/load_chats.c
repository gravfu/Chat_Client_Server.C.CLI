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

void add_chat(user_t *user, const char *chat_ref);

static void alloc_chat(chat_t **new_chat, const char *chat_ref);

void load_chats(user_t *user, const char *user_dir)
{
    char chat_info_path[4096] = {0};
    char chat_ref[42] = {0};
    const char *format = "ref: \"%[^\"]\"";
    FILE *chat_info = NULL;

    if (!user || !user_dir) return;
    sprintf(chat_info_path, "%s%s", user_dir, "/chat_info");
    chat_info = fopen(chat_info_path, "r");
    if (chat_info) {
        while (fscanf(chat_info, format, chat_ref) == 1) {
            add_chat(user, chat_ref);
            memset(chat_ref, 0, 42);
        }
        fclose(chat_info);
    }
}

void add_chat(user_t *user, const char *chat_ref)
{
    chat_t *list_cpy = user->chats;
    chat_t *new_chat = NULL;

    if (list_cpy == NULL)
        alloc_chat(&(user->chats), chat_ref);
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

chat_t *find_chat(chat_t *chat_list, const char *recipient)
{
    while (chat_list != NULL) {
        if (recipient && strstr(chat_list->chat_ref, recipient) != NULL)
            return (chat_list);
        chat_list = chat_list->next;
    }
    return (NULL);
}