##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile to build project
##

CC		=	gcc

FLAGS		=	-Werror -Wall -Wextra

SRC		=	main.c \
			socket_handle.c

OBJ     	=       $(SRC:.c=.o)

NAME    	=       myteams_cli

all:		$(NAME) $(NAME_QT)

$(NAME):	$(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)
		rm -f *~
		rm -f *#

fclean:		clean
		rm -f $(NAME)

re:		fclean all

auteur:
		echo $(USER) > auteur

.PHONY: 	all clean fclean re