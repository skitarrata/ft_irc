#ifndef	SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <string>
#include "../Client/Client.hpp"

class	Server
{
	private:
		int								fd; //da vedere dove prenderlo
		std::map<std::string, Client*>	clients;
		std::string						host;
		std::string						port;
	protected:
		std::map<std::string, Client*>::iterator iter;
	public:
		Server(std::string _port) : port(_port){};
		std::string		getport(){ return port; }
		std::string		gethost(){ return host; }
		void			sethost(std::string h){ host = h; }
		void			setport(std::string p){ port = p; }
//		void			addClient() non dimenticare di mandare un messaggio per accertarsi che la registrazione sia corretta
		Client *		searchClient(std::string key)
		{
			iter = clients.begin();
			while (iter != clients.end())
			{
				if (iter->first == key)
					return iter->second;
			}
			return NULL;
		}
		
		int				compareNick(std::string nick)
		{
			iter = clients.begin();
			while (iter != clients.end())
			{
				if (iter->first == nick)
					return 1;
			}
			return 0;
		}
		virtual ~Server(){};
};

#endif