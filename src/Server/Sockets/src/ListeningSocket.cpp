#include "../includes/ListeningSocket.hpp"

ListeningSocket::ListeningSocket() : BindingSocket() {}

ListeningSocket::ListeningSocket(const ListeningSocket & other)
        : _backlog(other._backlog),
          _listening(other._listening) {}

ListeningSocket::ListeningSocket(int domain,
	                                int service,
	                                int protocol,
	                                int port,
	                                u_long interface,
	                                int backlog)
	: BindingSocket(domain, service, protocol, port, interface),
    _backlog(backlog),
    _listening(0) {
    startListenToNetwork();
}

void ListeningSocket::Init(int port, int backlog) {
    _backlog = backlog;
    _listening = 0;
    SimpleSocket *ss_ptr = static_cast<SimpleSocket*>(this);
    BindingSocket *bs_ptr = static_cast<BindingSocket*>(this);
    ss_ptr->Init(AF_INET, SOCK_STREAM, PROTOCOL, port, INADDR_ANY);
    bs_ptr->connect();
    startListenToNetwork();
}

ListeningSocket::~ListeningSocket() {

	std::cout << RED << "\t[~] ListeningSocket destructor called." << RESET << std::endl;
}

void	ListeningSocket::startListenToNetwork() {

	// getSocketFD() here is the file descriptor of the server side socket
	_listening = listen(getSocketFD(), _backlog);

	testConnection(_listening);
}

int ListeningSocket::getBacklog() const {
    return _backlog;
}

int ListeningSocket::getListening() const {
    return _listening;
}


