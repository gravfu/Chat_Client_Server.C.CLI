/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** Recursively creates directories if they dont exist
*/

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int make_path(char *file_path, mode_t mode)
{
    if (!file_path || !(*file_path)) return (0);
    for (char *p = strchr(file_path + 2, '/'); p; p = strchr(p + 1, '/')) {
        *p = '\0';
        if (mkdir(file_path, mode) == -1) {
            if (errno != EEXIST) {
                *p = '/';
                return (0);
            }
        }
        *p = '/';
    }
    return (1);
}