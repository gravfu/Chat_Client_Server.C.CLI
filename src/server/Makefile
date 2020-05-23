##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile for my_teams server
##

SRC	=		./backup_loader/load_users.c			\
			./backup_loader/load_messages.c			\
			./commands/help_cmd.c					\
			./commands/login_cmd.c					\
			./commands/logout_cmd.c					\
			./commands/user_cmd.c					\
			./commands/users_cmd.c					\
			./connex_mgmt/accept_conn.c				\
			./connex_mgmt/connect_list_manips.c		\
			./connex_mgmt/get_sock.c				\
			./connex_mgmt/listen_for_conn.c			\
			./connex_mgmt/monitor_fds.c				\
			./connex_mgmt/recv_all.c				\
			./connex_mgmt/respond.c					\
			./connex_mgmt/send_all.c				\
			./connex_mgmt/server.c					\
			./main.c

OBJ 	=	$(SRC:.c=.o)

CC		=	gcc

CFLAGS 	+= 	-Werror -Wextra

LDFLAGS = 	-luuid

INCLUDE	= 	-I../../include

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
			$(RM) $(EXE)

re: 		fclean	all

.PHONY :
			all clean fclean re

.SILENT:
			all clean fclean re