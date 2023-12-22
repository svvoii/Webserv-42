#include "../includes/SimpleSocket.hpp"

SimpleSocket::SimpleSocket() {}


SimpleSocket::SimpleSocket(const SimpleSocket &other)
        : _socket_fd(other._socket_fd),
          _address(other._address),
          _domain(other._domain),
          _service(other._service),
          _protocol(other._protocol),
          _port(other._port),
          _interface(other._interface) {}

/*
** Default constructor
*/
SimpleSocket::SimpleSocket(int domain,
                           int service,
                           int protocol,
                           int port,
                           u_long anInterface) {
    Init(domain, service, protocol, port, anInterface);
}


void SimpleSocket::Init(int domain, int service, int aProtocol, int port,
                        u_long anInterface) {
    _domain = domain;
    _service = service;
    _protocol = aProtocol;
    _port = port;
    _interface = anInterface;
    // Defining address structure
    this->_address.sin_family = domain; // AF_INET;
    this->_address.sin_port = htons(port); // htons(PORT);
    this->_address.sin_addr.s_addr = htonl(anInterface); // INADDR_ANY;

    // Creating socket, getting file descriptor
    this->_socket_fd = socket(domain, service, aProtocol); // AF_INET = IPv4,
    // SOCK_STREAM = TCP, 0 = IP
    // error checking
    testConnection(this->_socket_fd);
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
int SimpleSocket::getSocketFD() const {
    return _socket_fd;
}

const sockaddr_in &SimpleSocket::getAddress() const {
    return _address;
}

int SimpleSocket::getDomain() const {
    return _domain;
}

int SimpleSocket::getService() const {
    return _service;
}

int SimpleSocket::getProtocol() const {
    return _protocol;
}

int SimpleSocket::getPort() const {
    return _port;
}

u_long SimpleSocket::getAnInterface() const {
    return _interface;
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



