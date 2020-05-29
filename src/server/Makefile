##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile for my_teams server
##

SRC	=		./backup_loader/drop_sub.c				\
			./backup_loader/load_channels.c			\
			./backup_loader/load_chats.c			\
			./backup_loader/load_subs.c				\
			./backup_loader/load_team_subs.c		\
			./backup_loader/load_teams.c			\
			./backup_loader/load_threads.c			\
			./backup_loader/load_users.c			\
			./commands/create_cmd.c					\
			./commands/create_resource.c			\
			./commands/get_comments.c				\
			./commands/help_cmd.c					\
			./commands/list_cmd.c					\
			./commands/list_resources.c				\
			./commands/login_cmd.c					\
			./commands/logout_cmd.c					\
			./commands/make_path.c					\
			./commands/messages_cmd.c				\
			./commands/send_cmd.c					\
			./commands/subscribe_cmd.c				\
			./commands/subscribed_cmd.c				\
			./commands/switch_context.c				\
			./commands/unsubscribe_cmd.c			\
			./commands/use_cmd.c					\
			./commands/user_cmd.c					\
			./commands/users_cmd.c					\
			./connex_mgmt/accept_conn.c				\
			./connex_mgmt/command_manip.c			\
			./connex_mgmt/connect_list_manips.c		\
			./connex_mgmt/get_sock.c				\
			./connex_mgmt/is_connected.c			\
			./connex_mgmt/listen_for_conn.c			\
			./connex_mgmt/monitor_fds.c				\
			./connex_mgmt/notification_manip.c		\
			./connex_mgmt/notify_many.c				\
			./connex_mgmt/recv_all.c				\
			./connex_mgmt/respond.c					\
			./connex_mgmt/send_all.c				\
			./connex_mgmt/server.c					\
			./main.c

OBJ 	=	$(SRC:.c=.o)

CC		=	gcc

LIB_DIR	=	../../libs/myteams

CFLAGS 	+= 	-Werror -Wextra

LDFLAGS = 	-L$(LIB_DIR) -lmyteams -luuid

TMS_HDR =	../../include

INCLUDE	= 	-I$(TMS_HDR) -I$(LIB_DIR)

NAME 	=	myteams_server

RM		=	rm -f

%.o: %.c
			$(CC) -g -c $< $(CFLAGS) $(INCLUDE) -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean	all

.PHONY :
			all clean fclean re

.SILENT:
			all clean fclean re