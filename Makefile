##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

RM	=	rm -f

all: 	server client

server:
		make -C ./src/server
		mv ./src/server/myteams_server ./

client:
		make -C ./src/client
		mv ./src/client/myteams_cli ./

clean:
		make clean -C ./src/server
		make clean -C ./src/client

fclean:
		make -C ./src/server fclean
		make -C ./src/client fclean
		$(RM) myteams_server
		$(RM) myteams_cli

re: fclean all

.PHONY:
	all server client clean fclean re

.SILENT:
	all server client clean fclean re