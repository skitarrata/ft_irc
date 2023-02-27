#ifndef UTILSCOM_HPP
#define UTILSCOM_HPP

#include <map>
#include "Command.hpp"

#define ERR_UNKNOWNCOMMAND(command)				"421 " + command + " :Unknown command"
#define ERR_NEEDMOREPARAMS(command)				"461 " + command + " :Not enough parameters"
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

#define RPL_WELCOME								"001 " + " :Welcome to the Internet Relay Network" // come implemento <nick>!<user>@<host> 
#define RPL_NAMREPLY(channel, users)			"353 " + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(channel)					"366 " + channel + " :End of NAMES list."

class UtilsCom
{
	private:
		std::map<std::string, Command*> com;
	protected:
		std::map<std::string, Command*>::iterator iter = com.begin();
	public:
		UtilsCom()
		{
			com["NICK"] = new comNick();
			com["USER"] = new comUser();
			com["PASS"] = new comPass();
			com["KICK"] = new comKick();
			com["PING"] = new comPing();
			com["PONG"] = new comPong();
			com["MODE"] = new comMode();
			com["JOIN"] = new comJoin();
			com["QUIT"] = new comQuit();
			com["PART"] = new comPart();
			com["NOTICE"] = new comNotice();
			com["PRIVMSG"] = new comPrivmsg();
		};

		Command*		searchCommand(std::string key)
		{
			while (iter != com.end())
			{
				if (iter->first == key)
					return iter->second;
			}
			return NULL;
		};
		~UtilsCom(){};
};

#endif