/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** recv_all
*/

#include"my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void add_new_arg(unsigned int *buff_loc, const char *buff, command_t *cmd);

static int find_next(int buff_loc, const char *buff, int limit);

static unsigned int is_start_cmd(int client_fd, command_t *cmd,
    unsigned int *buff_loc, const char *buff);

static void separate_args(char *buffer, int buff_size);

void new_recv(int client_fd, command_t *cmd)
{
    char buff[1024] = {0};
    int length = 0;
    unsigned int buff_loc = 0;
    unsigned int is_start = 0;

    memset(cmd->cmd, 0, MAX_COMMAND_LENGTH + 1);
    cmd->args = NULL;
    cmd->num_args = 0;
    length = read(client_fd, buff, 1023);
    separate_args(buff, length);
    for (int i = 0; length > 0; i++) {
        is_start = is_start_cmd(client_fd, cmd, &buff_loc, buff);
        if (is_start == 0) break;
        else if (is_start == 1) continue;
        if (i == 1) {
            strcpy(cmd->cmd, buff + buff_loc);
            buff_loc = find_next(buff_loc, buff, 1024);
        } else if (strcmp("END_COMM", buff + buff_loc) == 0) break;
        else add_new_arg(&buff_loc, buff, cmd);
    }
}

static void add_new_arg(unsigned int *buff_loc, const char *buff, command_t *cmd)
{
    cmd->num_args++;
    cmd->args = realloc(cmd->args, (cmd->num_args + 1) * sizeof(char *));
    cmd->args[cmd->num_args - 1] = strdup(buff + *buff_loc);
    cmd->args[cmd->num_args] = NULL;
    *buff_loc = find_next(*buff_loc, buff, 1024);
}

static int find_next(int buff_loc, const char *buff, int limit)
{
    int null_char = strchr(buff + buff_loc, '\0') - buff;

    while (buff[null_char] == '\0' && null_char < limit)
        null_char++;
    return (null_char);
}

static unsigned int is_start_cmd(int client_fd, command_t *cmd,
    unsigned int *buff_loc, const char *buff)
{
    if (*buff_loc == 0 && (strcmp("START_COMM", buff) != 0)) {
        strcpy(cmd->cmd, "Invalid");
        return (0);
    } else if (*buff_loc == 0 && (strcmp("START_COMM", buff) == 0)) {
        *buff_loc = find_next(*buff_loc, buff, 1024);
        return (1);
    }
    return (2);
}

static void separate_args(char *buffer, int buff_size)
{
    for (int i = 0; i < buff_size; i++) {
        if (buffer[i] == '\0' || buffer[i] == '\r' || buffer[i] == '\n')
            buffer[i] = '\0';
    }
}