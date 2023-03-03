#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "UtilsCom.hpp"

class	Command
{
	protected:
		std::string		namecom;
		Server*			serv; // definire la classe in seguito di server per i vari elementi che servono per le macro
	public:
		Command(Server* _serv) : serv(_serv){}
		virtual	void	functionCommand();
		virtual ~Command(){}
};

class comNick : public Command
{
	public:
		comNick(Server* serv) : Command(serv){}

		virtual void	functionCommand(Client* mit, std::string nick)
		{
			
			namecom = "NICK";
			if (nick.empty())
			{
				mit->write(ERR_NONICKNAMEGIVEN);
				return;
			}
			if (!mit->getrestricted())
			{
				if (serv->compareNick(nick))
				{
					mit->write(ERR_NICKNAMEINUSE(nick));
					return;
				}
				for (size_t i = 0; i < nick.size(); i++)
					if(nick[i] < 33 || nick[i] > 126)
					{
						mit->write(ERR_ERRONEUSNICKNAME(nick));
						return;
					}
				mit->setNickname(nick);
				mit->isRegistred();
			}
			else
				mit->write("operation DENIED for you!");
			return;
		}

		virtual ~comNick(){}
};

class comMode : public Command
{
	private:
		bool		sign;
	public:
		comMode(Server* serv) : Command(serv){}
		virtual void	functionCommand(Client* mit, std::string nick, std::string flag)
		{
			Client* cli;
			namecom = "MODE";
			if (nick.empty() || flag.empty())
			{
				cli->write(ERR_NEEDMOREPARAMS(namecom));
				return;
			}
			if (serv->compareNick(nick))
			{
				cli->write(ERR_USERSDONTMATCH);
				return;
			}
			if (flag.size() != 2)
			{
				cli->write(ERR_UMODEUNKNOWNFLAG);
				return;
			}
			if (!mit->getrestricted())
			{
				switch (flag[0])
				{
					case '-' :
						sign = 0;
						break;
					case '+' :
						sign = 1;
						break;
					default:
						cli->write(ERR_UMODEUNKNOWNFLAG);
						return;
				}

				switch (flag[1])
				{
					case 'i' :
						cli = serv->searchClient(nick);
						cli->invisible(sign);
						break;
					case 'w' :
						//come posso inviare messaggi solo agli OP?
						break;
					case 'r' :
						if (mit->getIRC_OP()) //se sei op puoi metterla agli altri
						{
							cli = serv->searchClient(nick);
							if (sign)
								cli->setrestricted(1);
							else
								cli->setrestricted(0);
						}
						else if (mit->getNickname() == nick) //a te stesso si
						{
							if (sign)
								mit->setrestricted(1);
							else
								mit->setrestricted(0);
						}
						else // ma agli altri no
							mit->write("operation DENIED for you!");
						break;
					case 'o' || 'O':
						if (mit->getIRC_OP())
						{
							cli = serv->searchClient(nick);
							if (sign)
								cli->setIRC_OP(1);
							else
								cli->setIRC_OP(0);
						}
						else
							mit->write("operation DENIED for you!");
						break;
					case 's' :
						//richiede sempre messaggi privati
						break;
					default:
						cli->write(ERR_UMODEUNKNOWNFLAG);
				}
			}
			else
				mit->write("operation DENIED for you!");
			return;
		}

		virtual ~comMode(){}
};

class comUser : public Command
{
	public:
		comUser(Server* serv) : Command(serv){}
		virtual void	functionCommand(Client* mit, std::string user, const char mod, const char sep, std::string realn)
		{
			namecom = "USER";
			if (user.empty() || !mod || !sep || realn.empty())
			{
				mit->write(ERR_NEEDMOREPARAMS(namecom));
				return;
			}
			if (sep != '*' || mod < '0' || mod > '7')
			{
				mit->write("Use this parameters: <user> <mode> <*> <realname>");
				return;
			}
			if (!mit->getrestricted())
			{
				if (mit->getregistred())
				{
					mit->write(ERR_ALREADYREGISTERED);
					return;
				}
				switch (mod)
				{
					case '2' :
						mit->invisible(1);
						break;
					case '3' :
						//come posso inviare messaggi solo agli OP?
						break;
					case '4' :
						mit->setrestricted(1);
						break;
					case '5' || '6':
						mit->write("operation DENIED for you!");
						break;
					case '7' :
						//richiede sempre messaggi privati
						break;
					default:
						mit->write(ERR_UMODEUNKNOWNFLAG);
				}
				mit->setusername(user);
				mit->setrealname(realn);
				mit->sethostname(serv->gethost());
				mit->isRegistred();
			}
			else
				mit->write("operation DENIED for you!");
			return;
		}

		virtual ~comUser(){}
};

class comPass : public Command
{
	public:
		comPass(Server* serv) : Command(serv){}
		virtual void	functionCommand(Client* mit, std::string pass)
		{
			namecom = "PASS";
			if (pass.empty())
			{
				mit->write(ERR_NEEDMOREPARAMS(namecom));
				return;
			}
			if (!mit->getrestricted())
			{
				if (mit->getregistred())
				{
					mit->write(ERR_ALREADYREGISTERED);
					return;
				}
				mit->setpassword(pass);
				mit->isRegistred();
			}
			else
				mit->write("operation DENIED for you!");
		}
		virtual ~comPass(){}
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