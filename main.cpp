#include <iostream>
#include <string>  //momentanei
#include <errno.h>

void		checkPriority(int ac, std::string port, std::string pass)
{
	if (ac != 3)
		throw std::invalid_argument("use this sintax ./ircserv <port> <password>\n");
	if (port.size() <= 0 || port.size() > 5)
		throw std::invalid_argument("bad port\n");
	if (pass.size() <= 0)
		throw std::invalid_argument("bad password\n");
	for(size_t i = 0; i < port.size(); i++)
		if (port[i] < 48 || port[i] > 57)
			throw std::invalid_argument("bad port\n");
	for(size_t i = 0; i < pass.size(); i++)
		if (pass[i] < 33 || pass[i] > 126)
			throw std::invalid_argument("bad password\n");
}

int		main(int ac, char *av[])
{
	try
	{
		checkPriority(ac, av[1], av[2]);
		return 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	
}