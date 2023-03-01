#ifndef UTILSCOM_HPP
#define UTILSCOM_HPP

#include <map>
#include <iostream>
#include <string>
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

#define ERR_UNKNOWNCOMMAND(command)				"421 " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(command)				"461 " + command + " :Not enough parameters"
#define ERR_ERRONEUSNICKNAME(nickname)			"432 " + nickname + " :Erroneous nickname"
#define ERR_NOTREGISTERED						"451 :You have not registered"
#define ERR_ALREADYREGISTERED					"462 :You may not reregister"
#define ERR_PASSWDMISMATCH						"464 :Password incorrect"
#define ERR_NONICKNAMEGIVEN						"431 :Nickname not given"
#define ERR_NICKNAMEINUSE(nickname)				"433 " + nickname + " :Nickname is already in use"
#define ERR_TOOMANYCHANNELS(channel)			"405 " + channel + " :You have joined too many channels"
#define ERR_NOTONCHANNEL(channel)				"442 " + channel + " :You're not on that channel"
#define ERR_NOSUCHCHANNEL(channel)				"403 " + channel + " :No such channel"
#define ERR_BADCHANNELKEY(channel)				"475 " + channel + " :Cannot join channel (+k)"
#define ERR_NOSUCHNICK(nickname)				"401 " + nickname + " :No such nick/channel"
#define ERR_USERNOTINCHANNEL(nickname, channel)	"441 " + nickname + " " + channel + " :They aren't on that channel"
#define ERR_CHANOPRIVSNEEDED(channel)			"482 " + channel + " :You're not channel operator"
#define ERR_CHANNELISFULL(channel)				"471 " + channel + " :Cannot join channel (+l)"
#define ERR_CANNOTSENDTOCHAN(channel)			"404 " + channel + " :Cannot send to channel"

#define RPL_WELCOME(nickname, users, host)		"001 :Welcome to the Internet Relay Network " + nickname + "!" + users + "@" + host
#define RPL_NAMREPLY(channel, users)			"353 " + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(channel)					"366 " + channel + " :End of NAMES list."

#endif