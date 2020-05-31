/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** my_teams_srv
*/

#ifndef MY_TEAMS_SRV_H_
#define MY_TEAMS_SRV_H_

#include <stddef.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <uuid/uuid.h>

#define  _GNU_SOURCE

#define MAX_COMMAND_LENGTH 12
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define MAX_PENDING 10
#define TIME_LEN 20

typedef struct command {
    char cmd[MAX_COMMAND_LENGTH + 1];
    char **args;
    unsigned int num_args;
    struct command *next;
} command_t;

typedef struct thread {
    char thread_title[MAX_NAME_LENGTH + 1];
    char thread_uuid[UUID_STR_LEN];
    char thread_init[MAX_BODY_LENGTH + 1];
    char timestamp[TIME_LEN];
    char user_uuid[UUID_STR_LEN];
    struct channel *p_channel;
    struct thread *next;
} thread_t;

typedef struct channel {
    char channel_name[MAX_NAME_LENGTH + 1];
    char channel_uuid[UUID_STR_LEN];
    char channel_desc[MAX_DESCRIPTION_LENGTH + 1];
    struct team *p_team;
    struct thread *threads;
    struct channel *next;
} channel_t;

typedef struct team {
    char team_name[MAX_NAME_LENGTH + 1];
    char team_uuid[UUID_STR_LEN];
    char team_desc[MAX_DESCRIPTION_LENGTH + 1];
    struct user *subs;
    struct channel *channels;
    struct team *next;
} team_t;

typedef struct chat {
    char chat_ref[42];
    struct chat *next;
} chat_t;

typedef struct user {
    char user_name[MAX_NAME_LENGTH + 1];
    char user_uuid[UUID_STR_LEN];
    struct team *team_subs;
    struct chat *chats;
    struct user *next;
} user_t;

typedef struct notification {
    char *msg;
    size_t msg_len;
    const user_t *rcvr;
    struct notification *next;
} notification_t;

typedef struct connex {
    int sock_fd;
    int logged_in;
    void *context;
    struct user *user;
    unsigned int team_cxt;
    unsigned int channel_cxt;
    unsigned int thread_cxt;
    struct connex *next;
} connex_t;

static const char *CMDS_STR[] = {"/help", "/login", "/logout", "/users",
    "/user", "/send", "/messages", "/subscribe", "/subscribed", "/unsubscribe",
    "/use", "/create", "/list", "/info"};

static connex_t *connect_list = NULL;

static const int NUM_CMDS = 14;

static const int MAX_CMD_LENGTH = 4096;

static const int MAX_CMD_NAME_LENGTH = 12;

static user_t *user_list = NULL;

static team_t *team_list = NULL;

int accept_conn(int server_fd, struct sockaddr_storage *client_addr);

void add_chann(team_t *p_team, const char *c_name, const char *c_uuid,
    const char *c_desc);

void add_chat(user_t *user, const char *chat_ref);

void add_connex(int fd);

void add_notification(const user_t *rcvr, const char *msg);

void add_sub(team_t *p_team, const char *s_name, const char *s_uuid);

void add_team(const char *c_name, const char *c_uuid, const char *c_desc);

void add_team_sub(user_t *p_user, const char *t_name, const char *t_uuid,
    const char *t_desc);

void add_thread(channel_t *p_channel, thread_t *to_copy);

void add_user(const char *u_name, const char *u_uuid);

void channel_switch(connex_t *user_connex, command_t *cmd);

void create_channel(connex_t *user_connex, command_t *cmd,
    const char *uuid_str);

void create_channel_dir(team_t *team, const char *c_name,
    const char *c_uuid_str, const char *c_desc);

void create_channel_response(const char *uuid_str, connex_t *user_connex);

void create_cmd(int fd, command_t *cmd);

void add_comment(thread_t *thread, const char *user_name,
    const char* comment);

int channel_exist(int sock_fd, command_t *cmd, team_t *team);

void create_comment(connex_t *user_connex, command_t *cmd);

void create_comment_response(connex_t *user_connex, command_t *cmd,
    const char *timestamp);

void create_thread_response(const char *uuid_str, connex_t *user_connex);

void create_team(connex_t *user_connex, command_t *cmd, const char *uuid_str);

void create_team_dir(const char *t_name, const char *t_uuid_str,
    const char *t_desc);

void create_team_response(const char *uuid_str, connex_t *user_connex);

void create_thread(connex_t *user_connex, command_t *cmd,
    const char *uuid_str);

void create_thread_file(connex_t *user_connex, thread_t *new_thread);

void delete_conn(int fd);

void del_notification(const notification_t *to_delete);

void del_sub(user_t **sub_list, const char *sub_name, const char *sub_uuid);

void del_team_sub(team_t **sub_list, const char *t_name, const char *t_uuid);

int drop_sub(team_t *team, const char *sub_name, const char *sub_uuid);

int drop_team_sub(user_t *user, const char *t_name, const char *t_uuid);

channel_t *find_channel(channel_t *channel_list, const char *channel_name,
    const char *channel_uuid);

chat_t *find_chat(chat_t *chat_list, const char *recipient);

connex_t *find_connex(int fd);

team_t *find_team(const char *team_name, const char *team_uuid);

team_t *find_team_sub(team_t *sub_list, const char *t_name,
    const char *t_uuid);

thread_t *find_thread(thread_t *thread_list, const char *thread_title,
    const char *thread_uuid);

user_t *find_user(const char *user_name, const char *user_uuid);

user_t *find_sub(user_t *sub_list, const char *sub_name,
    const char *sub_uuid);

char *get_comments_str(connex_t *user_connex);

const connex_t *get_connex(void);

char *get_channels_str(connex_t *user_connex);

const notification_t *get_notifications(void);

int get_sock(char *port);

const user_t *get_users(void);

const team_t *get_teams(void);

char *get_teams_str(void);

char *get_thread_body(const thread_t *thread);

char *get_threads_str(connex_t *user_connex);

char *get_users_str(void);

void help_cmd(int fd, command_t *cmd);

int is_connected(const user_t *user);

void launch_server(char *port);

void list_cmd(int fd, command_t *cmd);

void list_comments_response(connex_t *user_connex, const char *comments);

void list_threads_response(connex_t *user_connex, const char *threads);

void list_channels_response(connex_t *user_connex, const char *channels);

void list_teams_response(connex_t *user_connex, const char *teams);

void listen_for_conn(int listen_fd);

void load_channels(team_t *team, const char *team_dir);

void load_chats(user_t *user, const char *user_dir);

void load_subs(team_t *team, const char *team_dir);

void load_teams(void);

void load_team_subs(user_t *user, const char *user_dir);

void load_threads(channel_t *channel, const char *channel_dir);

void load_users(void);

void login_cmd(int fd, command_t *cmd);

void logout_cmd(int fd, command_t *cmd);

int make_path(char *file_path, mode_t mode);

void messages_cmd(int fd, command_t *cmd);

void monitor_fds(int *fd_max, fd_set *child_sets[2], fd_set *master_sets[2]);

void new_recv(int client_fd, command_t *cmd);

void no_switch(connex_t *user_connex);

void notify_connected(const char *message, user_t *ignore);

void notify_domain(const char *message, user_t *ignore);

void notify_team(team_t *team, const char *message, user_t *ignore);

void recv_all(int client_fd, command_t **cmd_list);

void respond(int fd, command_t *cmd);

void send_data(int client_fd, const char *buffer, int len);

void send_cmd(int fd, command_t *cmd);

void send_direct(int client_fd, const char *message);

void send_error(int error_num, int client_fd);

void send_responses();

int send_to_user(const connex_t *connections, const notification_t *notif);

void set_parent_chan(channel_t *p_chann);

void set_write_fds(fd_set *w_fds);

void subscribe_cmd(int fd, command_t *cmd);

void subscribed_cmd(int fd, command_t *cmd);

int team_exist(connex_t *user_connex, command_t *cmd);

void team_switch(connex_t *user_connex, command_t *cmd);

int thread_exist(int sock_fd, command_t *cmd, channel_t *channel);

void thread_switch(connex_t *user_connex, command_t *cmd);

void unsubscribe_cmd(int fd, command_t *cmd);

void use_cmd(int fd, command_t *cmd);

void user_cmd(int fd, command_t *cmd);

void users_cmd(int fd, command_t *cmd);

int user_exist(connex_t *user_connex, command_t *cmd);

static void (* const CMD_FUNCS[14])(int fd, command_t *cmd) = {
    &help_cmd,
    &login_cmd,
    &logout_cmd,
    &users_cmd,
    &user_cmd,
    &send_cmd,
    &messages_cmd,
    &subscribe_cmd,
    &subscribed_cmd,
    &unsubscribe_cmd,
    &use_cmd,
    &create_cmd,
    &list_cmd,
    NULL
};

#endif /* !MY_TEAMS_SRV_H_ */
