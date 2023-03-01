#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "UtilsCom.hpp"

class	Command
{
	protected:
		Server*		serv; // definire la classe in seguito di server per i vari elementi che servono per le macro
	public:
		Command(Server* _serv) : serv(_serv){};
		virtual	void	functionCommand() = 0;
		virtual ~Command(){};
};

class comNick : public Command
{
	public:
		comNick(Server* serv) : Command(serv){}

		virtual void	functionCommand(Client* cli, std::string nick)
		{
			if (nick.empty())
			{
				cli->write(ERR_NONICKNAMEGIVEN);
				return;
			}
			if (serv->compareNick(nick))
			{
				cli->write(ERR_NICKNAMEINUSE(nick));
				return;
			}
			for (size_t i = 0; i < nick.size(); i++)
				if(nick[i] < 33 || nick[i] > 126)
				{
					cli->write(ERR_ERRONEUSNICKNAME(nick));
					return;
				}
			cli->setNickname(nick);
			cli->welcome();
			return;
		}

		virtual ~comNick(){};
};

class comUser : public Command
{
	public:
		comUser(Server* serv) : Command(serv){};
		virtual void	functionCommand(Client* cli, std::string user, int mod, std::string realn)
		{

			cli->setusername(user);
			cli->setrealname(realn);
			cli->sethostname(serv->gethost());
			cli->welcome();
		}

		virtual ~comUser(){};
};

class comPass : public Command
{
	public:
		comPass(Server* serv){};
		virtual ~comPass(){};
};

class comKick : public Command
{
	public:
		com
		virtual ~com
};

class comPing : public Command
{
	public:
		com
		virtual ~com
};

class comPong : public Command
{
	public:
		com
		virtual ~com
};

class comMode : public Command
{
	public:
		com
		virtual ~com
};

class comJoin : public Command
{
	public:
		com
		virtual ~com
};

class comQuit : public Command
{
	public:
		com
		virtual ~com
};

class comPart : public Command
{
	public:
		com
		virtual ~com
};

class comNotice : public Command
{
	public:
		com
		virtual ~com
};

class comPrivmsg : public Command
{
	public:
		com
		virtual ~com
};

#endif