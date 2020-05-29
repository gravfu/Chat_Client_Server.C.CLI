/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help_cmd
*/

#include "help_cmd.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help_cmd(int fd, command_t *cmd)
{
    char *rsp = NULL;
    unsigned int rsp_len = 0;

    rsp_len = strlen("START_RSP\r\n") + strlen("000: List of TPC Commands:\r\n")
        + strlen(HELP_MSG) + strlen("END_RSP\r\n");
    rsp = calloc(rsp_len, sizeof(char));
    sprintf(rsp, "START_RSP\r\n%d\r\n%sEND_RSP\r\n",
        RSP_HELP, HELP_MSG);
    send_all(fd, rsp, strlen(rsp));
    free(rsp);
}