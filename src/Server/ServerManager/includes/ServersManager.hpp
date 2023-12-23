/*
** This class is set to create and manage the servers.
** The `Config` class will be used to get the data from the config file,
** and pass it to each server instance created.
**
** I/O MULTIPLEXING will be used to handle the connections to 
** each server with the help of the `select()` function, as well as
** the `fd_set` structure, and `fcntl()` function to set the socket
** to non-blocking mode.
*/
#ifndef SERVERSMANAGER_HPP
#define SERVERSMANAGER_HPP

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

#include "Server.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../../../Config/config/Config.h"

#include <arpa/inet.h> // inet_ntoa
#include <fcntl.h> // fcntl
#include <map> // std::map
#include <list> // std::list
#include <ctime> // std::time_t

typedef struct s_buffer {
	
	int				serverFd;
	std::string		requestBuffer;
	std::string		responseBuffer;
} t_buffer;

class ServersManager {
	private:

		const Config                &_config;
		std::list<Server>			_servers;

		fd_set						_recv_fd_pool; // To store the socket FDs of the clients
		fd_set						_send_fd_pool; // To store the socket FDs of the clients
		int							_max_fd; // To store the max socket FD

		void						_initFdSets();
		void						_addToSet(int fd, fd_set *set);
		void						_removeFromSet(int fd, fd_set *set);
		void						_closeConnection(int fd);

		void						_accept(int fd);
		void						_handle(int fd);
		void						_respond(int fd);

	public:
        explicit ServersManager(const Config &config);

        ~ServersManager();

		std::map<int, t_buffer>		clientsMap;

		// Main logic to run the servers, receive, handle and respond to the requests
		std::string					timeStamp();
		void						checkErrorAndExit(int returnValue, const std::string& msg);
		void						run();
		bool						isClient(int fd);

		// Setters
		void						initConfig();
		void						initServers();

};


#endif
