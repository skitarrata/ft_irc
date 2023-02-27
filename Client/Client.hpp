#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>

class Client
{
	private:
		std::string		nickname;
		std::string		password;
	public:
		Client() : nickname("newUser"), password(NULL){};
		void			setNickname(std::string nick){	nickname = nick; }
		void			setPassword(std::string pass){	password = pass; }
		std::string		getNickname(){	return nickname; }
		std::string		getPassword(){	return password; }
		virtual ~Client(){}
};

#endif