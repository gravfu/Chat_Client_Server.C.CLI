/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** login_cmd
*/

#include "logging_server.h"
#include "my_teams_srv.h"
#include "return_codes.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <uuid/uuid.h>

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd);

static void create_user_dir(const char *u_name, const char *u_uuid_str);

static user_t *create_user(command_t *cmd);

void login_cmd(int fd, command_t *cmd)
{
    char rsp[256] = {0};
    connex_t *user_connex = find_connex(fd);
    user_t *user = NULL;

    if (contains_errors(fd, user_connex, cmd)) return;
    user = find_user(cmd->args[0], NULL);
    if (!user)
        user = create_user(cmd);
    user_connex->logged_in = 1;
    user_connex->user = user;
    server_event_user_logged_in(user->user_uuid);
    sprintf(rsp, "START_RSP\r\n%d\r\nusername: \"%s\" useruuid: \"%s\"\r\n"
        "END_RSP\r\n", RSP_LOGIN, user->user_name, user->user_uuid);
    notify_connected(rsp, NULL);
}

static int contains_errors(int fd, connex_t *user_connex, command_t *cmd)
{
    if (user_connex->logged_in &&
        strcmp(user_connex->user->user_name, cmd->args[0]) == 0) {
        send_error(ERR_ALREADYCONNECTED, fd);
        return (1);
    }
    if (cmd->num_args == 0) {
        send_error(ERR_NEEDMOREPARAMS, fd);
        return (1);
    }
    if (cmd->num_args > 1) {
        send_error(ERR_TOOMANYPARAMS, fd);
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

static user_t *create_user(command_t *cmd)
{
    char u_uuid_str[UUID_STR_LEN] = {0};
    user_t *user = NULL;
    uuid_t u_uuid;

    uuid_generate(u_uuid);
    uuid_unparse_lower(u_uuid, u_uuid_str);
    add_user(cmd->args[0], u_uuid_str);
    user = find_user(cmd->args[0], u_uuid_str);
    create_user_dir(user->user_name, u_uuid_str);
    server_event_user_created(u_uuid_str, user->user_name);
    return (user);
}