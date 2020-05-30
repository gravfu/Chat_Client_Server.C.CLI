/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** create_resource
*/

#include "my_teams_srv.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void create_thread_info(channel_t *channel, thread_t *new_thread);

void create_team_dir(const char *t_name, const char *t_uuid_str,
    const char *t_desc)
{
    char t_dir_path[4096] = {0};
    const char *format = "./backup/teams/team_%s/";
    const char *team_format = "name: \"%s\" uuid: \"%s\" desc: \"%s\"\n";
    FILE *team_info = NULL;
    struct stat st = {0};

    sprintf(t_dir_path, format, t_uuid_str);
    make_path(t_dir_path, 0777);
    team_info = fopen("./backup/teams/team_info", "a+");
    fprintf(team_info, team_format, t_name, t_uuid_str, t_desc);
    fclose(team_info);
}

void create_channel_dir(team_t *team, const char *c_name,
    const char *c_uuid_str, const char *c_desc)
{
    char c_dir_path[4096] = {0};
    char c_info_path[4096] = {0};
    const char *chan_format = "name: \"%s\" uuid: \"%s\" desc: \"%s\"\n";
    const char *format = "./backup/teams/team_%s/channels/chan_%s/";
    const char *info_format = "./backup/teams/team_%s/channels/channel_info";
    FILE *channel_info = NULL;
    struct stat st = {0};

    sprintf(c_dir_path, format, team->team_uuid, c_uuid_str);
    sprintf(c_info_path, info_format, team->team_uuid);
    make_path(c_dir_path, 0777);
    channel_info = fopen(c_info_path, "a+");
    fprintf(channel_info, chan_format, c_name, c_uuid_str, c_desc);
    fclose(channel_info);
}

void create_thread_file(connex_t *user_connex, thread_t *new_thread)
{
    channel_t *channel = (channel_t *)user_connex->context;
    char t_file_path[4096] = {0};
    char time_str[TIME_LEN] = {0};
    const char *format = "./backup/teams/team_%s/channels/chan_%s/threads/"
        "thread_%s";
    FILE *thread = NULL;
    time_t now = time(NULL);

    create_thread_info(channel, new_thread);
    sprintf(t_file_path, format, channel->p_team->team_uuid,
        channel->channel_uuid, new_thread->thread_uuid);
    make_path(t_file_path, 0777);
    thread = fopen(t_file_path, "a+");
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(thread, "%s: %s: %s\r\n\n", user_connex->user->user_uuid,
        new_thread->thread_init, time_str);
    fclose(thread);
}

void create_thread_info(channel_t *channel, thread_t *new_thread)
{
    const char *info_format = "./backup/teams/team_%s/channels/chan_%s/"
        "/threads/thread_info";
    char t_info_path[4096] = {0};
    const char *thread_format = "u_uuid: \"%s\" title: \"%s\" uuid: \"%s\" "
        "init: \"%s\" time: \"%s\"\n";
    char time_str[TIME_LEN] = {0};
    FILE *thread_info = NULL;
    time_t now = time(NULL);

    sprintf(t_info_path, info_format, channel->p_team->team_uuid,
        channel->channel_uuid);
    make_path(t_info_path, 0777);
    thread_info = fopen(t_info_path, "a+");
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(thread_info, thread_format, new_thread->user_uuid,
        new_thread->thread_title, new_thread->thread_uuid,
        new_thread->thread_init, new_thread->thread_init);
    fclose(thread_info);
}

void add_comment(thread_t *thread, const char *user_uuid,
    const char* comment)
{
    channel_t *channel = thread->p_channel;
    char t_file_path[4096] = {0};
    char time_str[TIME_LEN];
    const char *format = "./backup/teams/team_%s/channels/chan_%s/threads/"
        "thread_%s";
    FILE *thread_file = NULL;
    time_t now = time(NULL);

    sprintf(t_file_path, format, channel->p_team->team_uuid,
        channel->channel_uuid, thread->thread_uuid);
    thread_file = fopen(t_file_path, "a+");
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(thread_file, "%s: %s: %s\r\n\n", user_uuid, comment, time_str);
    fclose(thread_file);
}