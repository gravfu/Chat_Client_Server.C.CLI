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

typedef struct {
    char cmd[MAX_COMMAND_LENGTH + 1];
    char **args;
    unsigned int num_args;
} command;

typedef struct thread {
    char thread_title[MAX_NAME_LENGTH + 1];
    char thread_uuid[UUID_STR_LEN];
    char thread_init[MAX_BODY_LENGTH + 1];
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

void add_sub(team_t *p_team, const char *s_name, const char *s_uuid);

void add_team(const char *c_name, const char *c_uuid, const char *c_desc);

void add_team_sub(user_t *p_user, const char *t_name, const char *t_uuid,
    const char *t_desc);

void add_thread(channel_t *p_channel, const char *t_title,
    const char *t_uuid, const char *t_init);

void add_user(const char *u_name, const char *u_uuid);

void channel_switch(connex_t *user_connex, command *cmd);

void create_channel_dir(team_t *team, const char *c_name,
    const char *c_uuid_str, const char *c_desc);

void create_cmd(int fd, command *cmd);

void create_comment(thread_t *thread, const char *user_name,
    const char* comment);

void create_team_dir(const char *t_name, const char *t_uuid_str,
    const char *t_desc);

void create_thread_file(channel_t *channel, const char *t_title,
    const char *t_uuid_str, const char *t_init);

void delete_conn(int fd);

void del_sub(user_t **sub_list, const char *sub_name, const char *sub_uuid);

void del_team_sub(team_t **sub_list, const char *t_name, const char *t_uuid);

int drop_sub(team_t *team, const char *sub_name, const char *sub_uuid);

int drop_team_sub(user_t *user, const char *t_name, const char *t_uuid);

channel_t *find_channel(channel_t *channel_list, const char *channel_name,
    const char *channel_uuid);

chat_t *find_chat(chat_t *chat_list, const char *recipient);

connex_t *find_connex(int fd);

team_t *find_team(const char *team_name, const char *team_uuid);

thread_t *find_thread(thread_t *thread_list, const char *thread_title,
    const char *thread_uuid);

user_t *find_user(const char *user_name, const char *user_uuid);

user_t *find_sub(user_t *sub_list, const char *sub_name, const char *sub_uuid);

char *get_comments_str(connex_t *user_connex);

char *get_channels_str(connex_t *user_connex);

int get_sock(char *port);

const user_t *get_users();

const team_t *get_teams();

char *get_teams_str();

char *get_threads_str(connex_t *user_connex);

void help_cmd(int fd, command *cmd);

void launch_server(char *port);

void list_cmd(int fd, command *cmd);

void listen_for_conn(int listen_fd);

void load_channels(team_t *team, const char *team_dir);

void load_chats(user_t *user, const char *user_dir);

void load_subs(team_t *team, const char *team_dir);

void load_teams();

void load_team_subs(user_t *user, const char *user_dir);

void load_threads(channel_t *channel, const char *channel_dir);

void load_users();

void login_cmd(int fd, command *cmd);

void logout_cmd(int fd, command *cmd);

int make_path(char *file_path, mode_t mode);

void monitor_fds(int *fd_max, fd_set *read_fds, fd_set *master);

void new_recv(int client_fd, command *cmd);

void no_switch(connex_t *user_connex);

void respond(int fd, command *cmd);

void send_all(int client_fd, const char *buffer, int len);

void send_cmd(int fd, command *cmd);

void send_error(int error_num, const char *msg, int client_fd);

void subscribe_cmd(int fd, command *cmd);

void subscribed_cmd(int fd, command *cmd);

void team_switch(connex_t *user_connex, command *cmd);

void thread_switch(connex_t *user_connex, command *cmd);

void unsubscribe_cmd(int fd, command *cmd);

void use_cmd(int fd, command *cmd);

void user_cmd(int fd, command *cmd);

void users_cmd(int fd, command *cmd);

static void (* const CMD_FUNCS[14])(int fd, command *cmd) = {
    &help_cmd,
    &login_cmd,
    &logout_cmd,
    &users_cmd,
    &user_cmd,
    &send_cmd,
    NULL,
    &subscribe_cmd,
    &subscribed_cmd,
    &unsubscribe_cmd,
    &use_cmd,
    &create_cmd,
    &list_cmd,
    NULL
};

#endif /* !MY_TEAMS_SRV_H_ */
