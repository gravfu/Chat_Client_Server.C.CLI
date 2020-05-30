/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** command_manip
*/

#include "my_teams_srv.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_to_cmds(command_t **cmd_list, command_t *new_cmd)
{
    command_t *list_cpy = *cmd_list;

    if (*cmd_list == NULL)
        *cmd_list = new_cmd;
    else {
        while (list_cpy->next != NULL)
            list_cpy = list_cpy->next;
        list_cpy->next = new_cmd;
    }
}

command_t *alloc_cmd(void)
{
    command_t *new_cmd = NULL;

    if ((new_cmd = malloc(sizeof(command_t))) == NULL) {
        printf("Error allocation. Send error to lib\n");
        exit(84);
    }
    memset(new_cmd->cmd, 0, MAX_COMMAND_LENGTH + 1);
    new_cmd->args = NULL;
    new_cmd->num_args = 0;
    new_cmd->next = NULL;
    printf("%p\n", new_cmd);
    return (new_cmd);
}