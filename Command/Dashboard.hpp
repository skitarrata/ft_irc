#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include "Command.hpp"

class Dashboard
{
	private:
		std::map<std::string, Command*> com;
	protected:
		std::map<std::string, Command*>::iterator iter = com.begin();
	public:
		Dashboard()
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
		~Dashboard(){};
};

#endif