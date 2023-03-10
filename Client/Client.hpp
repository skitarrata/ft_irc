#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Command/UtilsCom.hpp"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

#define RPL_WELCOME(nickname, users, host)		"001 :Welcome to the Internet Relay Network " + nickname + "!" + users + "@" + host

class Client
{
	private:
		//permessi per gli utenti
		bool			IRC_OP = 0; //per diventare admin
		bool			restricted = 0; //per non fare usare i comandi agli utenti, solo un irc op puo farlo
		bool			reciveNotice = 0; //per ricevere notizie dal server
		bool			registred = 0;
		std::string		remember;

		//interfaccia utente
		std::string		nickname = NULL;
		std::string		pass = NULL;
		std::string		username = NULL;
		std::string		realname = NULL;
		std::string		hostname = NULL; //hostname è uguale per tutti i client?

		//Clients
		int				fd;
		int				port;
		std::string		whichChannel;
		
	public:
		Client(int _fd, std::string host, int _port) : fd(_fd), hostname(host), port(_port){}
		
		//metodi get e set
		void			setNickname(std::string nick){	nickname = nick; }
		void			sethostname(std::string host){	hostname = host; }
		void			setusername(std::string user){	username = user; }
		void			setrealname(std::string real){	realname = real; }
		void			setpass(std::string p){ pass = p; }
		void			setrestricted(bool n){ restricted = n; }
		void			setIRC_OP(bool n){ IRC_OP = n; }
		void			setwhichChannel(std::string name){ whichChannel = name; }
		std::string		getwhichChannel(){ return whichChannel; }
		std::string		getrealname(){ return realname; }
		std::string		getpass(){ return pass; }
		std::string		getusername(){ return username; }
		std::string		getNickname(){ return nickname; }
		std::string		gethostname(){ return hostname; }
		int				getport(){ return port; }
		bool			getrestricted(){ return restricted; }
		bool			getregistred(){ return registred; }
		bool			getIRC_OP(){ return IRC_OP; }
		int				getfd(){ return fd; }

		//metodi utili per la classe
		void			write(std::string msg)
		{
			if(send(fd, msg.c_str(), msg.length(), 0) < 0)
				throw std::runtime_error("Error sending message.");
		}

		void			isRegistred()
		{
			if (!nickname.empty() && !pass.empty() && !username.empty() && !realname.empty() && !hostname.empty())
			{
				write(RPL_WELCOME(nickname, username, hostname));
				registred = 1;
			}
			return;
		}

		void			invisible(bool s) //gestire il set e il get name
		{
			if (s)
			{
				remember = nickname;
				nickname = "invisible";
			}
			else if(nickname == "invisible")
				nickname = remember;
			else
				return;
		}
		
		virtual ~Client(){}
};

#endif