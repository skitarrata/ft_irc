#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "../Client/Client.hpp"

#define MAX	1024

class Channel
{
	private:
		int						dimc = 0;
		const std::string		password;
		std::string				nameChannel;
		std::vector<Client*>	Clients; //teniamop traccia di tutti gli user, inclusi quelli delle altre categorie
		std::vector<Client*>	Admin;
	protected:
		std::vector<Client*>::iterator it;
	public:
		Channel(std::string name, const std::string pass, Client* admin) : nameChannel(name), password(pass){}
		//vedere come trattare l'admin
		std::string				getnameChannel(){return nameChannel;}
		int						getdim(){return dimc;}

		void					Overflowdim()
		{
			if(dimc == MAX)
				throw std::runtime_error("The channel is full!!\n");
		}
		void					isEmpty()
		{
			if(dimc == 0)
				throw std::runtime_error("The channel is empty!!\n");
		}
		void					addClient(Client* client)
		{
			Overflowdim();
			Clients.push_back(client);
			dimc++;
		}
		void					addAdmin(Client* client)
		{
			addClient(client);
			Admin.push_back(client);
		}
		void					removeClient(Client* admin, Client* c)
		{
			isEmpty();
			if(!c->getIRC_OP() && admin->getIRC_OP())
			{
				Clients.erase(std::remove(Clients.begin(), Clients.end(), c), Clients.end());
				dimc--;
			}
			else
				throw std::runtime_error("you don't have permission!!\n");
		}
/* 		void					removeAdmin(Client* c, Client* admin)
		{
			isEmpty();
			if(!c->getIRC_OP() && admin->getIRC_OP())
				Clients.erase(std::remove(Clients.begin(), Clients.end(), c), Clients.end());
			if(c->getIRC_OP())
			dimc--;
		} */
		virtual ~Channel(){};
};

#endif