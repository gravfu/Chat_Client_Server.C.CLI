##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile to build project
##

CC		=	gcc

CFLAGS		=	-Werror -Wall -Wextra

SRC		=	main.c \
			socket_handle.c \
			parser_func.c

OBJ     	=       $(SRC:.c=.o)

NAME    	=       myteams_cli

TMS_HDR =	../../include

LIB_DIR	=	../../libs/myteams

LDFLAGS = 	-L$(LIB_DIR) -lmyteams -luuid

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