#include "../includes/ConnectingSocket.hpp"

/*
** This class is similar to BindingSocket class except that it uses
** `connect()` instead of `bind()` in the `connectToNetwork()` method.
** This represents a client side socket.
**
** In the constructor of this class we call the constructor of the
** parent class and pass the arguments to it.
*/
ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long interface)
	: SimpleSocket(domain, service, protocol, port, interface) {

	std::cout << MAGENTA << "\t[ ConnectingSocket ] constructor called." << RESET << std::endl;

	_connectStatus = 0;

	// Establish connection, bind the socket to a port, check for error
	connectToNetwork(this->getSocketFD(), this->getAddress());
}

ConnectingSocket::~ConnectingSocket() {

	std::cout << RED << "\t[~] ConnectingSocket destructor called." << RESET << std::endl;
}

// Getters
int		ConnectingSocket::getConnectStatus() const {

	return (this->_connectStatus);
}

/*
** This method is used to connect the socket to a port.
** It is a virtual method in the parent class and must be implemented here.
*/
void	ConnectingSocket::connectToNetwork(int socket_fd, struct sockaddr_in address) {

	// Establishing connection to the network on the client side
	_connectStatus = connect(socket_fd, (struct sockaddr *)&address, sizeof(address));
	// error check
	testConnection(this->_connectStatus);
}
