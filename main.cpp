#include <iostream>
#include <string>  //momentanei
#include <errno.h>

void		checkPriority(int ac, std::string port, std::string pass)
{
	if (ac != 3)
		throw std::out_of_range("use this sintax ./ircserv <port> <password>\n");
	if (port.length() <= 0 || port.length() > 5)
		throw std::out_of_range("bad port\n");
	if (pass.length() <= 0)
		throw std::out_of_range("bad password\n");
	for(int i = 0; i < port.length(); i++)
		if (port[i] < 48 || port[i] > 57)
			throw std::invalid_argument("bad port\n");
	for(int i = 0; i < pass.length(); i++)
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
		return EPERM;  //equivale a return 1;
	}
	
}