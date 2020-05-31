##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile to build project
##

CC		=	gcc

CFLAGS		=	-Werror -Wall -Wextra

SRC		=	main.c \
			response_parser.c \
			socket_handle.c \
			parser_func.c \
			lib_func_handle/loggedin.c \
			lib_func_handle/loggedout.c \
			lib_func_handle/notif_private_message.c \
			lib_func_handle/rsp_user.c \
			lib_func_handle/notif_team_created.c \
			lib_func_handle/notif_thread_message.c \
			lib_func_handle/notif_channel_created.c \
			lib_func_handle/notif_thread_created.c \
			lib_func_handle/rsp_team_subscribe.c \
			lib_func_handle/rsp_team_unsubscribe.c \
			lib_func_handle/rsp_reply_comment.c \
			lib_func_handle/rsp_thread_created.c \
			lib_func_handle/rsp_channel_created.c \
			lib_func_handle/err_client_exist.c \
			lib_func_handle/rsp_team_created.c \
			lib_func_handle/err_client_unautorized.c \
			lib_func_handle/err_unknown_user.c \
			lib_func_handle/err_unknown_channel.c \
			lib_func_handle/err_unknown_team.c \
			lib_func_handle/err_unknown_thread.c \
			lib_func_handle/rsp_users.c \
			lib_func_handle/rsp_list_team.c \
			lib_func_handle/rsp_list_channel.c \
			lib_func_handle/rsp_list_thread.c \
			lib_func_handle/rsp_info_team.c \
			lib_func_handle/rsp_messages_command.c

OBJ     	=       $(SRC:.c=.o)

NAME    	=       myteams_cli

TMS_HDR =	../../include

LIB_DIR	=	../../libs/myteams

LDFLAGS = 	-L$(LIB_DIR) -lmyteams

INCLUDE	= 	-I$(TMS_HDR) -I$(LIB_DIR)

RM		=	rm -f

%.o: %.c
			$(CC) -g -c $< $(CFLAGS) $(INCLUDE) -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)
		$(RM) *~
		$(RM) *#

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

auteur:
		echo $(USER) > auteur

.PHONY:
			all clean fclean re

.SILENT:
			all clean fclean re
