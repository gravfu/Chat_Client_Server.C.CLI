/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** get_thread_body
*/

#include <stdio.h>
#include <stdlib.h>

char *get_thread_body()
{
    FILE *thread = fopen("textfile.txt", "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = 0;
}