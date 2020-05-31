/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** parser_func
*/

#include "parser_func.h"
#include <time.h>

char *var_parser(char *buffer, char *to_searsh)
{
    char *variable = strstr(buffer, to_searsh);
    char *gui1, *gui2, *new, *tmp;
    int i;
    if (variable == NULL)
        return NULL;
    gui1 = strstr(variable, "\"");
    if (gui1 == NULL)
        return NULL;
    gui2 = strstr(gui1 + 1, "\"");
    if (gui2 == NULL || gui1 == gui2)
        return NULL;
    tmp = gui1;
    for (i = 0; tmp != gui2 - 1; i++, tmp++);
    new = malloc(sizeof(char) * (i + 5));
    memset(new, 0, i + 4);
    strncpy(new, gui1 + 1, gui2 - gui1 - 1);
    new[gui2 - gui1] = '\0';
    return new;
}

char *var_parser_body(char *buffer, char *to_searsh)
{
    char *variable = strstr(buffer, to_searsh);
    char *gui1, *gui2, *tmp, *new;
    int i;
    if (variable == NULL)
        return NULL;
    gui1 = strstr(variable, " ");
    if (gui1 == NULL)
        return NULL;
    gui2 = strstr(gui1 + 1, "\n");
    if (gui2 == NULL || gui1 == gui2)
        return NULL;
    tmp = gui1;
    for (i = 0; tmp != gui2 - 1; i++, tmp++);
    new = malloc(sizeof(char) * (i + 5));
    memset(new, 0, i + 4);
    strncpy(new, gui1 + 1, gui2 - gui1 - 2);
    new[gui2 - gui1 - 1] = '\0';
    return new;
}

void remove_char(char *s, int c)
{
    int j = 0;
    int i = 0;
    int n = strlen(s);
    for (i = 0; i<n; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

time_t string_to_time_t(char *buffer)
{
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    if (!buffer) {
        return 0;
    }
    strptime(buffer, "%Y-%m-%d %H:%M:%S", &tm);
    return mktime(&tm);
}
