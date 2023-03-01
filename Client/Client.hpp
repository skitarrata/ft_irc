#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Command/UtilsCom.hpp"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

class Client
{
	private:
		int				fd;
		std::string		port;
		std::string		nickname;
		std::string		username;
		std::string		realname;
		std::string		hostname;
	public:
		Client(int _fd, std::string _port) : fd(_fd), port(_port){}
		void			setNickname(std::string nick){	nickname = nick; }
		void			sethostname(std::string host){	hostname = host; }
		void			setusername(std::string user){	username = user; }
		void			setrealname(std::string real){	realname = real; }
		std::string		getrealname(){	return realname; }
		std::string		getusername(){	return username; }
		std::string		getNickname(){	return nickname; }
		std::string		gethostname(){	return hostname; }
		std::string		getport(){ return port; }
		int				getfd(){ return fd; }
		void			write(std::string msg)
		{
			if(send(fd, msg.c_str(), msg.length(), 0) < 0)
				throw std::runtime_error("Error sending message.");
		}
		void			welcome(){ write(RPL_WELCOME(nickname, username, hostname)); }
		virtual ~Client(){}
};

#endif