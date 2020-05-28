/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** send_cmd
*/

#include "logging_server.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void add_chat_info(user_t *user, const char *rcvr_uuid);

static void add_messages_to_chats(user_t *user, command *cmd);

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static void send_message(connex_t *user_connex, command *cmd);


void send_cmd(int fd, command *cmd)
{
    connex_t *user_connex = find_connex(fd);
    char rsp[256];

    if (contains_errors(fd, user_connex, cmd))
        return;
    send_message(user_connex, cmd);
    sprintf(rsp, "START_RSP\r\n%d\r\nEND_RSP\r\n", RSP_SEND);
    send_all(fd, rsp, strlen(rsp));
    server_event_private_message_sended(user_connex->user->user_uuid,
        cmd->args[0], cmd->args[1]);
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    user_t *user = NULL;

    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, "Not logged in.", fd);
        return (1);
    }
    if (cmd->num_args > 2) {
        send_error(ERR_TOOMANYPARAMS, "Too many parameters.", fd);
        return (1);
    }
    if (cmd->num_args < 2) {
        send_error(ERR_NEEDMOREPARAMS, "Missing parameters.", fd);
        return (1);
    }
    user = find_user(NULL, cmd->args[0]);
    if (!user) {
        send_error(ERR_NOSUCHUSER, "Invalid recipient.", fd);
        return (1);
    }
    return (0);
}

static void send_message(connex_t *user_connex, command *cmd)
{
    chat_t *sender_chat = find_chat(user_connex->user->chats, cmd->args[0]);
    user_t *recipient = find_user(NULL, cmd->args[0]);
    chat_t *rcvr_chat = find_chat(recipient->chats,
        user_connex->user->user_uuid);

    if (!sender_chat || !rcvr_chat) {
        add_chat_info(user_connex->user, cmd->args[0]);
        add_chat_info(recipient, user_connex->user->user_uuid);
    }
    add_messages_to_chats(user_connex->user, cmd);
}

static void add_messages_to_chats(user_t *user, command *cmd)
{
    char sender_path[4096] = {0};
    char receiver_path[4096] = {0};
    FILE *sender_chat = NULL;
    FILE *receiver_chat = NULL;

    sprintf(sender_path, "./backup/users/usr_%s/chat_%s", user->user_uuid,
        cmd->args[0]);
    sprintf(receiver_path, "./backup/users/usr_%s/chat_%s", cmd->args[0],
        user->user_uuid);
    sender_chat = fopen(sender_path, "a+");
    receiver_chat = fopen(receiver_path, "a+");
    fprintf(sender_chat, "%s: %s\r\n\n", user->user_uuid, cmd->args[1]);
    fprintf(receiver_chat, "%s: %s\r\n\n", user->user_uuid, cmd->args[1]);
    fclose(sender_chat);
    fclose(receiver_chat);
}

static void add_chat_info(user_t *user, const char *rcvr_uuid)
{
    char chat_info_path[4096] = {0};
    char chat_ref[42] = {0};
    chat_t *chat = find_chat(user->chats, rcvr_uuid);
    FILE *chat_info = NULL;

    if (!chat) {
        sprintf(chat_ref, "chat_%s", rcvr_uuid);
        add_chat(user, chat_ref);
        sprintf(chat_info_path, "./backup/users/usr_%s/chat_info",
            user->user_uuid);
        chat_info = fopen(chat_info_path, "a+");
        fprintf(chat_info, "ref: \"chat_%s\"", rcvr_uuid);
        fclose(chat_info);
    }
}