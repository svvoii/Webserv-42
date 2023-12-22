#include <iostream>
#include "../includes/ServersManager.hpp"

ServersManager::ServersManager(const Config &config)
: _config(config) {
    std::cout << MAGENTA << "\tServersManager default constructor called" << RESET << std::endl;

    initServers();

    run();
}

ServersManager::~ServersManager() {

	std::cout << RED << "\tServersManager destructor called" << RESET << std::endl;
}

void	ServersManager::initConfig() {

	// This function is for testing purposes only !!!
	// The hardcoded data in `Config` class shall be parsed from the config file.
//	_config.setServersData();
//	_numberOfServers = _config.numberOfServers;
//
//	std::cout << YELLOW << "[!] Number of servers: " << _numberOfServers << RESET << std::endl;

}

void	ServersManager::initServers() {

//	_servers.reserve(_numberOfServers);


    _servers.push_back(Server(*_config.getConstServers().begin()));
    _servers.back().initServerSocket();

//    for (l_sc_c_it it = _config.getConstServers().begin();
//        it != _config.getConstServers().end(); ++it) {
//
//        _servers.push_back(Server(*it));
//        _servers.back().initServerSocket();
//    }
}

void	ServersManager::_initFdSets() {

	FD_ZERO(&_recv_fd_pool);
	FD_ZERO(&_send_fd_pool);
	int	fcntl_ret = 0;
	int	serverFd = 0;
	_max_fd = 0;

	for (size_t i = 0; i < _config.getConstServers().size(); i++) {

		serverFd = _servers[i].getServerFd();

		fcntl_ret = fcntl(serverFd, F_SETFL, O_NONBLOCK);
		checkErrorAndExit(fcntl_ret, "fcntl() failed. Exiting..");

		_addToSet(serverFd, &_recv_fd_pool);

		_max_fd = serverFd;
	}
}

void	ServersManager::_addToSet(int fd, fd_set *set) {

	if (fd > _max_fd) {
		_max_fd = fd;
	}
	FD_SET(fd, set);
}

void	ServersManager::_removeFromSet(int fd, fd_set *set) {

	if (fd == _max_fd) {
		_max_fd--;
	}
	FD_CLR(fd, set);
}

void	ServersManager::_closeConnection(int fd) {
	std::cout << timeStamp() << YELLOW << "[!] Closing connection with fd:[" << fd << "]." << RESET << std::endl;

	if (FD_ISSET(fd, &_recv_fd_pool)) {
		_removeFromSet(fd, &_recv_fd_pool);
	}
	if (FD_ISSET(fd, &_send_fd_pool)) {
		_removeFromSet(fd, &_send_fd_pool);
	}
	close(fd);
	clientsMap.erase(fd);
}

std::string	ServersManager::timeStamp() {

	std::time_t currentTime = std::time(NULL);
    std::tm* now = std::localtime(&currentTime);
    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "[%d/%m/%Y %H:%M:%S]", now);

	return std::string(buffer);
}

void	ServersManager::checkErrorAndExit(int returnValue, const std::string& msg) {

	if (returnValue == -1) {

		std::cerr << RED << "\t[-]" << msg << RESET << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	ServersManager::run() {

	fd_set	recv_fd_pool_copy;
	fd_set	send_fd_pool_copy;
	int		select_ret = 0;

	_initFdSets();

	while (true) {

		recv_fd_pool_copy = _recv_fd_pool;
		send_fd_pool_copy = _send_fd_pool;

		select_ret = select(_max_fd + 1, &recv_fd_pool_copy, &send_fd_pool_copy, NULL, NULL);
		checkErrorAndExit(select_ret, "select() failed. Exiting..");

		for (int fd = 3; fd <= _max_fd; fd++) {

			if (FD_ISSET(fd, &recv_fd_pool_copy) && !isClient(fd)) {

				_accept(fd);
			}
			else if (FD_ISSET(fd, &recv_fd_pool_copy) && isClient(fd)) {

				_handle(fd);
			}
			else if (FD_ISSET(fd, &send_fd_pool_copy)) {

				_respond(fd);

				// CGI handling ?!
			}
		}
		// check for timeout ?!
	}
}

void	ServersManager::_accept(int fd) {

	struct sockaddr_in	address;
	socklen_t			address_len = sizeof(address);
	int					fcntl_ret = 0;
	int					serverFd = fd;

	fd = accept(serverFd, (struct sockaddr *)&address, (socklen_t *)&address_len);
	if (fd == -1) {
		std::cerr << RED << "\t[-] Error accepting connection.. accept() failed..";
		std::cerr << " serverFd: [" << serverFd << "], fd:[" << fd << "]" << std::endl;
		std::cerr << RESET << std::endl;
		return ;
	}

	std::cout << timeStamp() << GREEN << "[+] New connection to [" << _servers[serverFd - 3].getServerName() << "] fd:[" << serverFd << "], client fd:[" << fd << "], IP:[" << inet_ntoa(address.sin_addr) << "]" << RESET << std::endl;

	_addToSet(fd, &_recv_fd_pool);

	fcntl_ret = fcntl(fd, F_SETFL, O_NONBLOCK);
	if (fcntl_ret == -1) {
		std::cerr << RED << "\t[-] Error setting socket to non-blocking mode.. fcntl() failed." << RESET << std::endl;
		_closeConnection(fd);
		return ;
	}

	t_buffer buff;

	buff.serverFd = serverFd;
	buff.requestBuffer = "";
	buff.responseBuffer = "";

	clientsMap.insert(std::make_pair(fd, buff));
}

void	ServersManager::_handle(int fd) {

	char	buffer[BUF_SIZE] = {0};
	int		bytes_read = 0;

	bytes_read = read(fd, buffer, BUF_SIZE);

	std::cout << timeStamp();

	if (bytes_read == 0) {
		std::cout << YELLOW << "[!] bytes_read == 0 from client fd:[" << fd << "]" << RESET << std::endl;
		//std::cout << YELLOW << "[!] Connection closed by the client. ";
		_closeConnection(fd);
		return ;
	}
	else if (bytes_read < 0) {
		std::cerr << RED << "[-] Error reading data from the client.. read() failed." << RESET << std::endl;
		_closeConnection(fd);
		return ;
	}

	clientsMap[fd].requestBuffer.append(buffer, bytes_read);

	std::cout << CYAN << "[*] Request received from client fd:[" << fd << "]" << RESET << std::endl;

	HttpRequest 	httpRequest(clientsMap[fd].requestBuffer);

	HttpResponse	response(&httpRequest);
	clientsMap[fd].responseBuffer = response.getResponse();

	// might need to check if the body is not empty and handle CGI and other stuff

	_removeFromSet(fd, &_recv_fd_pool);
	_addToSet(fd, &_send_fd_pool);
}

void	ServersManager::_respond(int fd) {

	int		bytes_sent = 0;
	int		bytes_to_send = clientsMap[fd].responseBuffer.length();

	bytes_sent = send(fd, clientsMap[fd].responseBuffer.c_str(), bytes_to_send, 0);

	std::cout << timeStamp();

	if (bytes_sent == -1) {
		std::cerr << RED << "[-] Error sending data to the client.. send() failed." << RESET << std::endl;
		_closeConnection(fd);
		return ;
	}
	else if (bytes_sent < bytes_to_send) {
		std::cout << YELLOW << "[!] Not all data has been sent to the client. " << RESET << std::endl;
		clientsMap[fd].responseBuffer.erase(0, bytes_sent);
		return ;
	}
	else {
		std::cout << GREEN << "[+] Response sent to client fd:[" << fd << "]" << RESET << std::endl;
	}

	_removeFromSet(fd, &_send_fd_pool);
	_addToSet(fd, &_recv_fd_pool);

	clientsMap[fd].requestBuffer.clear();
	clientsMap[fd].responseBuffer.clear();
}

bool	ServersManager::isClient(int fd) {

	return clientsMap.count(fd) > 0;
}


