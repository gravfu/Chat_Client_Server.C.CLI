/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** parser_func
*/

#include "parser_func.h"

char *var_parser(char *buffer, char *to_searsh)
{
    char *variable = strstr(buffer, to_searsh);
    if (variable == NULL)
        return NULL;
    char *gui1 = strstr(variable, "\"");
    if (gui1 == NULL)
        return NULL;
    char *gui2 = strstr(gui1 + 1, "\"");
    if (gui2 == NULL || gui1 == gui2)
        return NULL;
    char *new = malloc(sizeof(char) * 257);
    memset(new, 0, 257);
    strncpy(new, gui1 + 1, gui2 - gui1 - 1);
    new[gui2 - gui1] = '\0';
    return new;
}