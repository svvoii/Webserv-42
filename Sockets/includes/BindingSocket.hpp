#ifndef BINDINGSOCKET_HPP
#define BINDINGSOCKET_HPP

#include "SimpleSocket.hpp"

/*
** This class will be used to create a socket and bind it to a port.
** It will inherit from SimpleSocket class.
**
** This class will be used to create a server side socket 
** using `bind()` in the `connectToNetwork()` method.
*/
class BindingSocket : public SimpleSocket {
	private:

		int	_bindStatus;

	public:

		BindingSocket(int domain, int service, int protocol, int port, u_long interface);
		~BindingSocket();

		// Getters
		int	getBindStatus() const;

		// This method is virtual in parent and must be implemented by the child class. 
		void	connectToNetwork(int socket_fd, struct sockaddr_in address);
};

#endif
