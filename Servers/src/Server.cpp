#include "../includes/Server.hpp"

Server::Server(t_serverData *serverData) 
	: 
	_serverSocket(NULL),
	_serverFd(-1),
	_port(serverData->port),
	_serverName(serverData->serverName),
	_uploadpath(serverData->uploadPath),
	_locations_map(serverData->locations_map) {

	std::cout << MAGENTA << "\tServer constructor called" << RESET << std::endl;

}

Server::~Server() {

	std::cout << RED << "\tServer destructor called" << RESET << std::endl;

	delete _serverSocket;
}

void	Server::initServerSocket() {

	_serverSocket = new ListeningSocket(AF_INET, SOCK_STREAM, PROTOCOL, _port, INADDR_ANY, BACKLOG);
	_serverFd = _serverSocket->getSocketFD();
}

ListeningSocket	*Server::getServerSocket() const {

	return _serverSocket;
}

int		Server::getServerFd() const {

	return _serverFd;
}

std::string	Server::getServerName() const {

	return _serverName;
}

/*
** This function is for testing purposes only !!!
** PRINTS THE SERVER DATA
*/
void	Server::printServerData() const {

	std::cout << YELLOW << "[!] Server DATA:" << RESET << std::endl;
	std::cout << YELLOW << "\tServer fd: " << _serverFd << RESET << std::endl;
	std::cout << YELLOW << "\tServer port: " << _port << RESET << std::endl;
	std::cout << YELLOW << "\tServer name: " << _serverName << RESET << std::endl;
	std::cout << YELLOW << "\tServer upload path: " << _uploadpath << RESET << std::endl;
	std::cout << YELLOW << "\tServer locations: " << RESET << std::endl;

	std::map<std::string, t_locationsData>::const_iterator it = _locations_map.begin();
	std::map<std::string, t_locationsData>::const_iterator ite = _locations_map.end();

	while (it != ite) {

		std::cout << YELLOW << "\t\tLocation: " << it->second.location << RESET << std::endl;
		std::cout << YELLOW << "\t\tRoot: " << it->second.root << RESET << std::endl;
		std::cout << YELLOW << "\t\tAllowed methods: " << RESET << std::endl;

		for (size_t i = 0; i < it->second.allowedMethods.size(); i++) {

			std::cout << YELLOW << "\t\t\t" << it->second.allowedMethods[i] << RESET << std::endl;
		}

		std::cout << YELLOW << "\t\tIndexes: " << RESET << std::endl;

		for (size_t i = 0; i < it->second.indexes.size(); i++) {

			std::cout << YELLOW << "\t\t\t" << it->second.indexes[i] << RESET << std::endl;
		}

		it++;
	}

}
