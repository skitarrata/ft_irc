#ifndef	SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
//#include "../Client/Client.hpp"
#include "../Command/Dashboard.hpp"
#include "../Channel/Channel.hpp"
#include <stdlib.h>
#include <poll.h>

#define HOST "127.0.0.1"

class	Server
{
	private:
		int								sock; //da vedere dove prenderlo
		std::map<std::string, Client*>	clients;
		std::vector<Channel*>			channels;
		std::vector<pollfd>				pollfds;

		std::string						host;
		const std::string				port;
		const std::string				password;
		
		Dashboard*						dash;
	protected:
		std::map<std::string, Client*>::iterator	itcli;
		std::vector<Channel*>::iterator				itcha;
		std::vector<pollfd>::iterator				itpoll;
	public:
		Server(std::string _port, std::string _pass) : port(_port), password(_pass), host(HOST)
		{
			sock = newSocket();
			dash = new Dashboard(this);
		}
		~Server(){ delete dash;}
		std::string		getport(){ return port; }
		std::string		getpassword(){ return password; }
		std::string		gethost(){ return host; }
		Channel*		getchannel(std::string name)
		{
			for (itcha = channels.begin(); itcha != channels.end(); itcha++)
				if (itcha.operator*()->getnameChannel() == name)
					return itcha.operator*();
			return NULL;
		}
		void			sethost(std::string h){ host = h; }

		void			launchServer()
		{
			pollfd		serverfd = {sock, POLLIN, 0};
			pollfds.push_back(serverfd);

			while (1)
			{
				if (poll(pollfds.begin().base(), pollfds.size(), -1) < 0)
					throw std::runtime_error("Error poll from fd!!\n");
				
				//connect end disconnect client 
			}
		}

		int				newSocket()
		{
			int fds;
			if((fds = socket(AF_INET, SOCK_STREAM, 0)) < 0)
				throw std::runtime_error("Connection Failled: socket not connected\n");
			int opt = 1;
			if (setsockopt(fds, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt)))
				throw std::runtime_error("Connection Failled: fail opt\n");
			//da come richisto dal sub, usiamo non-blocking per gli fd
			if (fcntl(fds, F_SETFL, O_NONBLOCK) < 0)
				throw std::runtime_error("Connection Failled: error set NON_BLOCKING\n");
			
			struct sockaddr_in	addr;
			socklen_t			addrlen = sizeof(addr);
			//per pulire la struttura, in modo da non creare segmentation fault;
			bzero((char *) &addr, addrlen);
			addr.sin_family = AF_INET;
    		addr.sin_addr.s_addr = INADDR_ANY;
    		addr.sin_port = htons(std::atoi(port.c_str())); //vedere se funziona l'atoi cosi

			if (bind(fds, (struct sockaddr*)&addr, addrlen)< 0)
				throw std::runtime_error("Connection Failled: fail bind\n");
			if (listen(fds, 1024) < 0)
				throw std::runtime_error("Connection Failled: fail listen\n");
			return fds;
		}

		void			clientConnect()
		{
			int fd;
			sockaddr_in	addr = {};
			socklen_t addrlen = sizeof(addr);

			if((fd = accept(sock, (sockaddr*)&addr, &addrlen)) < 0)
				throw std::runtime_error("accepting fail!!\n");
			
			pollfd pollfd = {fd, POLLIN, 0};
			pollfds.push_back(pollfd);

			char hostname[NI_MAXHOST];
			if (getnameinfo((struct sockaddr *) &addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV))
				throw std::runtime_error("Error hostname for new client.");
			Client *client = new Client(fd, hostname, ntohs(addr.sin_port));
			clients.insert(std::make_pair(fd, client));  //??

			//messaggio per aver effettuato la connessione e messaggio per accertarsi che la registrazione sia corretta
		}

		void			clientDisconnect(std::string nick)
		{
			int fd;
			if (!compareNick(nick))
				throw std::invalid_argument("nickname is incorrect!!\n");
			Client* cli = clients.at(nick);
			fd = cli->getfd();

			//come lo scollego dal canale ?
			//dobbiamo prima creare un canale per fare questo

			clients.erase(nick);
			for (itpoll = pollfds.begin(); itpoll != pollfds.end(); itpoll++)
			{
				if (itpoll->fd == fd)
				{
					pollfds.erase(itpoll);
					close(fd);
					break;
				}
			}
			delete cli;
		}
		
		void			createchannel(const std::string name, const std::string pass, Client* admin)
		{
			Channel *channel = new Channel(name, password, admin);
			channels.push_back(channel);
		}

		Client *		searchClient(std::string key)
		{
			itcli = clients.begin();
			while (itcli != clients.end())
			{
				if (itcli->first == key)
					return itcli->second;
			}
			return NULL;
		}
		
		int				compareNick(std::string nick)
		{
			itcli = clients.begin();
			while (itcli != clients.end())
			{
				if (itcli->first == nick)
					return 1;
			}
			return 0;
		}
};

#endif