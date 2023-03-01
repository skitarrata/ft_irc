#ifndef	SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include "../Client/Client.hpp"

class	Server
{
	private:
		int						fd; //da vedere dove prenderlo
		std::vector<Client*>	clients;
		std::string				password;
		std::string				host;
		std::string				port;
	protected:
		std::vector<Client*>::iterator iter;
	public:
		Server(std::string _port, std::string _pass) : port(_port), password(_pass){};
		std::string		getport(){ return port; }
		std::string		getpassword(){ return password; }
		std::string		gethost(){ return host; }
		void			sethost(std::string h){ host = h; }
		void			setport(std::string p){ port = p; }
		void			setpassword(std::string p){ password = p; }
		void			addClient(){ clients.push_back(new Client(fd, port)); }
		int				compareNick(std::string nick)
		{
			for (iter = clients.begin(); iter != clients.end(); iter++)
				if (iter.operator*()->getNickname() == nick)
					return 1;
			return 0;
		}
		virtual ~Server(){};
};

#endif