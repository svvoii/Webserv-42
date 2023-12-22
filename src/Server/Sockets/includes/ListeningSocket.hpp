#ifndef LISTENINGSOCKET_HPP
#define LISTENINGSOCKET_HPP

#define PROTOCOL 0
#define BACKLOG 10

#include "BindingSocket.hpp"

/*
** This class will be used to create a Listening socket 
** based on the BindingSocket class.
**
** `int listen(int sockfd, int backlog);` 
** this function shall be used in the `connectToNetwork()` method
** implementation. So, `socket_fd` and `backlog` shall be handled. 
** (for more on `listen` see QUICK_REF_FUNCTIONS.md)
**
** We are adding `backlog` to the constructor of this class.
** which will be the maximum length to which the queue of 
** pending connections for `socket_fd` may grow. 
** Every next connection (after the backlog is full) will be rejected.
*/

class ListeningSocket : public BindingSocket {
	private:

		int	_backlog; // maximum length of the pending connections queue
		int	_listening; // return value of `listen()`

	public:
        ListeningSocket();
        ListeningSocket(int domain,
                        int service,
                        int protocol,
                        int port,
                        u_long interface,
                        int backlog);
        ListeningSocket(const ListeningSocket &);

		// virtual destructor is needed a child class is inheriting from this class
		virtual ~ListeningSocket();

		// Getters
        int getBacklog() const;
        int getListening() const;

    void	startListenToNetwork();

    void Init(int port, int backlog);
};

#endif
