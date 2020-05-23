/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login_cmd
*/

#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>

static int contains_errors(int fd, connex_t *user_connex, command *cmd);

static void create_user_dir(const char *u_name, const char *u_uuid_str);

void login_cmd(int fd, command *cmd)
{
    char rsp[256] = {0};
    char u_uuid_str[37];
    connex_t *user_connex = find_connex(fd);
    uuid_t u_uuid;
    user_t *user = NULL;

    if (contains_errors(fd, user_connex, cmd)) return;
    user = find_user(cmd->args[0], NULL);
    if (!user) {
        uuid_generate(u_uuid);
        uuid_unparse_lower(u_uuid, u_uuid_str);
        add_user(cmd->args[0], u_uuid_str);
        user = find_user(cmd->args[0], NULL);
        create_user_dir(user->user_name, u_uuid_str);
    }
    user_connex->logged_in = 1;
    user_connex->user = user;
    sprintf(rsp, "%d: %s", RSP_LOGIN, "Login successful\n");
    send_all(fd, rsp, strlen(rsp));
}

static int contains_errors(int fd, connex_t *user_connex, command *cmd)
{
    if (user_connex->logged_in &&
        strcmp(user_connex->user->user_name, cmd->args[0]) == 0) {
        send_error(ERR_ALREADYCONNECTED, "Already logged in.\n", fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, "Missing parameters.\n", fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, "Too many paramters.\n", fd);
        return (1);
    }
    return (0);
}

static void create_user_dir(const char *u_name, const char *u_uuid_str)
{
    char u_dir_path[4096] = {0};
    const char *format = "./backup/users/usr_%s";
    const char *usr_format = "name: \"%s\" uuid: \"%s\"\n";
    FILE *user_info = NULL;
    struct stat st = {0};

    sprintf(u_dir_path, format, u_uuid_str);
    if (stat("./backup", &st) == -1)
        mkdir("./backup", 0777);
    if (stat("./backup/users", &st) == -1)
        mkdir("./backup/users", 0777);
    mkdir(u_dir_path, 0777);
    user_info = fopen("./backup/users/user_info", "a+");
    fprintf(user_info, usr_format, u_name, u_uuid_str);
    fclose(user_info);
}