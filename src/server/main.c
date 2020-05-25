/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** Main function for my_ftp project
*/

#include "my_teams_srv.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int is_number(char *num);

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        printf("USAGE:\t./myteams_server port\n"
            "\tport is the port number on which the server socket listens.\n");
    } else if (argc == 2 && is_number(argv[1])) {
        load_teams();
        load_users();
        launch_server(argv[1]);
    } else {
        printf("USAGE:\t./myteams_server port\n"
            "\tport is the port number on which the server socket listens.\n");
        return (84);
    }
}

static int is_number(char *num)
{
    for (int i = 0; num[i] != '\0'; i++) {
        if (!isdigit(num[i]))
            return (0);
    }
    return (1);
}