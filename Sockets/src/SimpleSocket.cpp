#include "../includes/SimpleSocket.hpp"

/*
** Default constructor
*/
SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface) {

	std::cout << MAGENTA << "\t[ SimpleSocket - parrent ] constructor called." << RESET << std::endl;

	// Defining address structure
	this->_address.sin_family = domain; // AF_INET;
	this->_address.sin_port = htons(port); // htons(PORT);
	this->_address.sin_addr.s_addr = htonl(interface); // INADDR_ANY;

	// Creating socket, getting file descriptor 
	this->_socket_fd = socket(domain, service, protocol); // AF_INET = IPv4, SOCK_STREAM = TCP, 0 = IP
	// error checking
	testConnection(this->_socket_fd);

	std::cout << GREEN << "\t[+] Socket created successfully. _socket_fd = " << this->_socket_fd << RESET << std::endl; 

}

/*
** Default destructor
*/
SimpleSocket::~SimpleSocket() {

	std::cout << RED << "\t[~] SimpleSocket destructor called." << RESET << std::endl;

	// This might leak when server is interrupted with ctrl+c
	close(this->_socket_fd);
}

/*
** Getters
*/
int		SimpleSocket::getSocketFD() const {

	return (this->_socket_fd);
}

struct sockaddr_in	SimpleSocket::getAddress() const {

	return (this->_address);
}

/*
** Setters
void	SimpleSocket::setSocketFD(int socket_fd) {

	this->_socket_fd = socket_fd;
}
*/

/*
** This method is used to test the established connection
** The return from `connect()` or `bind()` is used as an argument
*/
void	SimpleSocket::testConnection(int itemToTest) {

	if (itemToTest < 0) {
		
		perror("In itemToTest");
		exit(EXIT_FAILURE);
	}
}
