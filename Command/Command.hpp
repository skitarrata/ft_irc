#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include "../Client/Client.hpp"
#include "../Server/Server.hpp"

class	Command
{
	protected:
		Server*		_serv; // definire la classe in seguito di server per i vari elementi che servono per le macro
	public:
		Command(Server* serv) : _serv(serv){};
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
				//errore
			cli->setNickname(nick); 
		}

		virtual ~comNick(){};
};

class comUser : public Command
{
	public:
		comUser(Server* serv){};
		virtual ~comUser(){}
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