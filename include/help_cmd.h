/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** help_cmd
*/

#ifndef HELP_CMD_H_
#define HELP_CMD_H_

static const char *HELP_MSG =
    "/help : show help\r\n"
    "/login [“username”] : set the username used by client\r\n"
    "/logout : disconnect the client from the server\r\n"
    "/users : get the list of all users that exist on the domain\r\n"
    "/user [“user_uuid”] : get information about a user\r\n"
    "/send [“user_uuid”] [“message_body”] : send a message to a user\r\n"
    "/messages [“user_uuid”] : list all messages exchange with an user\r\n"
    "/subscribe [“team_uuid”] : subscribe to the event of a team and its sub"
        " directories (enable reception of all events from a team)\r\n"
    "/subscribed ?[“team_uuid”] : list all subscribed teams or list all users"
        " subscribed to a teamr\r\n"
    "/unsubscribe [“team_uuid”] : unsubscribe from a team\r\n"
    "/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : use specify a"
        " context team/channel/thread\r\n"
    "/create : based on what is being used create the sub resource\r\n"
    "/list : based on what is being used list all the sub resources\r\n"
    "/info : based on what is being used list the current (see below)\r\n";

#endif /* !HELP_CMD_H_ */
