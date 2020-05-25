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

static void add_new_arg(unsigned int *buff_loc, const char *buff, command *cmd);

static int find_next(int current_idx, const char *buff);

static unsigned int is_start_cmd(int client_fd, command *cmd,
    unsigned int *buff_loc, const char *buff);

static void separate_args(char *buffer, int buff_size);



// void check_end_line(char *buffer, int buff_size);

// static void add_new_arg(const char* buff, command *cmd);

// char *recv_all(int client_fd)
// {
//     static char buff[256];
//     char *input = NULL;
//     int length = 0;
//     int total = 0;

//     while ((length = read(client_fd, buff, 255)) > 0) {
//         check_end_line(buff, length);
//         length = (length == (int)strlen(buff)) ? length : (int)strlen(buff);
//         total += length;
//         if (total == length)
//             input = calloc(total + 1, sizeof(char));
//         else
//             input = realloc(input, total);
//         strcat(input, buff);
//         input[total] = '\0';
//         if (length != 255) {
//             memmove(buff, buff + length, 255 - length);
//             break;
//         } else memset(buff, 0, 256);
//     }
//     return (input);
// }

// void check_end_line(char *buffer, int buff_size)
// {
//     for (int i = 0; i < buff_size; i++) {
//         if (buffer[i] == '\0' || buffer[i] == '\r' || buffer[i] == '\n') {
//             buffer[i] = '\0';
//             return;
//         }
//     }
// }

void new_recv(int client_fd, command *cmd)
{
    static char buff[MAX_DESCRIPTION_LENGTH + 1] = {0};
    int length = 0;
    unsigned int buff_loc = 0;
    unsigned int is_start = 0;

    memset(cmd->cmd, 0, MAX_COMMAND_LENGTH + 1);
    cmd->args = NULL;
    cmd->num_args = 0;
    length = read(client_fd, buff, MAX_DESCRIPTION_LENGTH);
    separate_args(buff, length);
    for (int i = 0; length > 0; i++) {
        is_start = is_start_cmd(client_fd, cmd, &buff_loc, buff);
        if (is_start == 0) break;
        else if (is_start == 1) continue;
        if (i == 1) {
            strcpy(cmd->cmd, buff + buff_loc);
            buff_loc = find_next(buff_loc, buff);
        } else if (strcmp("END_COMM", buff + buff_loc) == 0) break;
        else add_new_arg(&buff_loc, buff, cmd);
    }
}

static void add_new_arg(unsigned int *buff_loc, const char *buff, command *cmd)
{
    cmd->num_args++;
    cmd->args = realloc(cmd->args, (cmd->num_args + 1) * sizeof(char *));
    cmd->args[cmd->num_args - 1] = strdup(buff + *buff_loc);
    cmd->args[cmd->num_args] = NULL;
    *buff_loc = find_next(*buff_loc, buff);
}

static int find_next(int buff_loc, const char *buff)
{
    int null_char = strchr(buff + buff_loc, '\0') - buff;

    while (buff[null_char] == '\0')
        null_char++;
    return (null_char);
}

static unsigned int is_start_cmd(int client_fd, command *cmd,
    unsigned int *buff_loc, const char *buff)
{
    if (*buff_loc == 0 && (strcmp("START_COMM", buff) != 0)) {
        strcpy(cmd->cmd, "Invalid");
        return (0);
    } else if (*buff_loc == 0 && (strcmp("START_COMM", buff) == 0)) {
        *buff_loc = find_next(*buff_loc, buff);
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