/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help_cmd
*/

#include "my_teams_srv.h"
#include <string.h>

void help_cmd(int fd, command *cmd)
{
    send_all(fd, "START_CMD\r\n", 11);
    for (int i = 0; i < NUM_CMDS; i++)
        send_all(fd, HELP_MSGS[i], strlen(HELP_MSGS[i]));
    send_all(fd, "END_CMD\r\n", 9);
    // if (strcmp("", cmd->args) == 0) {
    //     send_all(fd, "214 System OK. Enter a specfic for more information"
    //         " on it.\n", 59);
    //     return;
    // } else {
    //     for (int i = 0; i < NUM_CMDS; i++) {
    //         if (strcmp(cmd->args, CMDS_STR[i]) == 0) {
    //             send_all(fd, HELP_MSGS[i], strlen(HELP_MSGS[i]));
    //             return;
    //         }
    //     }
    // }
    // send_all(fd, "START_CMD", 9);
    // send_all(fd, "xxx Error (RFC compliant)\n", 26);
}