#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include "Command.hpp"

class Dashboard  //vedere se conviene estendere a command
{
	private:
		std::map<std::string, Command*>	com;
		Server*							serv;
	protected:
		std::map<std::string, Command*>::iterator iter = com.begin();
	public:
		Dashboard(Server* _serv) : serv(_serv)
		{
			com["NICK"] = new comNick(serv);
			com["MODE"] = new comMode(serv);
			com["USER"] = new comUser(serv);
			com["PASS"] = new comPass(serv);
/* 			com["KICK"] = new comKick();
			com["PING"] = new comPing();
			com["PONG"] = new comPong();
			com["JOIN"] = new comJoin();
			com["QUIT"] = new comQuit();
			com["PART"] = new comPart();
			com["NOTICE"] = new comNotice();
			com["PRIVMSG"] = new comPrivmsg(); */
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
		~Dashboard(){};
};

#endif


//Il comando PASS viene utilizzato per impostare una 'password di connessione'. La password facoltativa può e DEVE essere impostata prima di qualsiasi tentativo di registrazione della connessione. Attualmente ciò richiede che l'utente invii un comando PASS prima di inviare la combinazione NICK/USER