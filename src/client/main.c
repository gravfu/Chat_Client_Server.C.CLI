/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019 [WSL: Ubuntu]
** File description:
** main
*/

#include <stdio.h>
#include "socket_handle.h"

int main(int argc, char **argv)
{
    int serv_port;

    if (argc == 1 && strcmp(argv[1], "--help"))

    if (argc != 3)
        return 84;
    serv_port = atoi(argv[2]);
    if (serv_port <= 0 || serv_port > 65535) {
        fprintf(stderr, "Port must be between 1 and 65535\n");
        return 84;
    }
    return socket_handle(serv_port, argv[1]);
}