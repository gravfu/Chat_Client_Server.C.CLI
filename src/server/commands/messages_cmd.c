/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** messages_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

char *get_messages_str(connex_t *user_connex, command_t *cmd);

static void init_str(int iteration, char *str, int len_str);

static char *read_messages(FILE *thread_file);

void messages_cmd(int fd, command_t *cmd)
{
    char *rsp = NULL;
    char *chat_str = NULL;
    connex_t *user_connex = find_connex(fd);
    unsigned int len_str = 0;
    unsigned int rsp_len = 0;

    if (contains_errors(fd, user_connex, cmd))
        return;
    chat_str = get_messages_str(user_connex, cmd);
    len_str = (chat_str != NULL) ? strlen(chat_str) : 0;
    rsp_len = strlen("START_RSP\r\n000\r\n") + len_str +
        strlen("END_RSP\r\n") + 1;
    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n", RSP_MESSAGES, chat_str);
    if (chat_str) free(chat_str);
    add_notification(user_connex->user, rsp);
    free(rsp);
}

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd)
{
    user_t *user = NULL;

    if (!user_connex->user || !user_connex->logged_in) {
        send_error(ERR_NOTCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, fd);
        return (1);
    }
    user = find_user(NULL, cmd->args[0]);
    if (!user) {
        send_error(ERR_NOSUCHUSER, fd);
        return (1);
    }
    return (0);
}

char *get_messages_str(connex_t *user_connex, command_t *cmd)
{
    char *chat_str = NULL;
    char chat_path[4096] = {0};
    FILE *chat_file = NULL;
    const thread_t *thread = (thread_t *)(user_connex->context);
    user_t *usr = user_connex->user;
    int i = 0;

    sprintf(chat_path, "./backup/users/usr_%s/chat_%s", usr->user_uuid,
        cmd->args[0]);
    chat_file = fopen(chat_path, "r");
    if (chat_file) {
        chat_str = read_messages(chat_file);
        fclose(chat_file);
    }
    return (chat_str);
}

static char *read_messages(FILE *chat_file)
{
    char buff[1024] = {0};
    char msg_body[MAX_BODY_LENGTH + 1] = {0};
    char *chat_str = NULL;
    const char *format = "%[^:]: %[^:]: %[^\r\n\r\n]\r\n\r\n";
    char time_str[TIME_LEN] = {0};
    char u_uuid[UUID_STR_LEN] = {0};
    int i = 0;
    int length = 0;

    while (fscanf(chat_file, format, u_uuid, msg_body, time_str) == 3) {
        sprintf(buff, "useruuid: \"%s\" time: \"%s\" body: %s\r\n",
            u_uuid, time_str, msg_body);
        length += strlen(buff);
        chat_str = realloc(chat_str, (length + 1) * sizeof(char));
        init_str(i++, chat_str, length + 1);
        strcat(chat_str, buff);
        memset(buff, 0, 1024);
    }
    return (chat_str);
}

static void init_str(int iteration, char *str, int len_str)
{
    if (iteration == 0)
        memset(str, 0, len_str * sizeof(char));
}