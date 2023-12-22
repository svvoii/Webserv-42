#ifndef SIMPLESOCKET_HPP
#define SIMPLESOCKET_HPP

#include <iostream>
#include <string>
#include <cstdio> // perror()
#include <cstdlib> // exit()
#include <unistd.h> // close()
#include <sys/socket.h> // socket(), bind(), listen(), accept()
#include <netinet/in.h> // sockaddr_in, INADDR_ANY
#include <sys/types.h>  // for u_long
#include <sys/select.h> // for fd_set

// SOME COLORS FOR DEBUGGING
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

/*
** This goingto be the parent class for TCP or UDP sockets
** and will be an abstract class, with no instances possible.
**
** This class will provide the basic interface for two main
** types of sockets: server side and client side.
**
** `BindingSocket` will inherit from this class and offer 
** functionality for server side sockets with `bind()`.
**
** `ConnectingSocket` will inherit from this class and offer
** functionality for client side sockets with `connect()`.
**
** Additionally, `ListeningSocket` will be a child class of
** `BindingSocket` and will offer functionality for server side
** to listen for incoming connections with `listen()`.
*/
class SimpleSocket {
	private:

        int					_socket_fd; // this will be the file descriptor returned by `socket()`
		struct sockaddr_in	_address;

        int _domain;
        int _service;
        int _protocol;
        int _port;
        u_long _interface;
public:
        SimpleSocket();
        SimpleSocket(const SimpleSocket &);
        SimpleSocket(int domain,
                     int service,
                     int aProtocol,
                     int port,
                     u_long anInterface);

//		SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
		~SimpleSocket();

		// Getters

        int getSocketFD() const;
        const sockaddr_in &getAddress() const;
        int getDomain() const;
        int getService() const;
        int getProtocol() const;
        int getPort() const;
        u_long getAnInterface() const;

		// Setters
		// void				setSocketFD(int socket_fd);

        void Init(int domain, int service, int aProtocol, int port,
                  u_long anInterface);
		// This must be implemented by the child class. 
		// In the implementation either `bind()` or `connect()` to be used (SERVER vs CLIENT)
		virtual void	connectToNetwork(int socket_fd, struct sockaddr_in address) = 0;

		// This will simply check the return value of `bind()` or `connect()` and exit if < 0
		void			testConnection(int itemToTest);

};

#endif