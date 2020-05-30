/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019 [WSL: Debian]
** File description:
** parser_func
*/

#ifndef PARSER_FUNC_H_
#define PARSER_FUNC_H_

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char *var_parser(char *buffer, char *to_searsh);
char *var_parser_body(char *buffer, char *to_searsh);
void remove_char(char *s, int c);

#endif /* !PARSER_FUNC_H_ */
