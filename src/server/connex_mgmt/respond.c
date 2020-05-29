/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** Respond to the entered command
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <string.h>

void respond(int fd, command_t *cmd)
{
    for (int i = 0; i < NUM_CMDS; i++) {
        if (strcmp(cmd->cmd, CMDS_STR[i]) == 0 && CMD_FUNCS[i]) {
            CMD_FUNCS[i](fd, cmd);
            return;
        }
    }
    send_error(ERR_INVALIDCOMMAND, fd);
}