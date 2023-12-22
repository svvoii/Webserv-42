#include "../includes/HttpRequest.hpp"

/*
*/
HttpRequest::HttpRequest(const std::string& buffer) {
/*
	std::cout << MAGENTA << "\tHttpRequest constructor called." << RESET << std::endl;
	std::cout << CYAN << "Parsing HTTP request.." << RESET << std::endl;
*/
	std::istringstream	ss(buffer);
	std::string			line;

	// Parsing each line into map by the first space
	while (std::getline(ss, line) && !line.empty() && line != "\r") {

		line = trim(line);

		_parseHeaders(line);
	}

	// Extracting the request line, method, uri, http version
	_extractRequestLine();

	// Extracting the body of the request
	while (std::getline(ss, line)) {
		_bodyBuffer += line;
	}
}

HttpRequest::~HttpRequest() {
	
	//std::cout << RED << "\t[~] HttpRequest destructor called." << RESET << std::endl;
}

void	HttpRequest::_parseHeaders(const std::string& line) {

	//std::cout << CYAN << "in parseLine().." << RESET << std::endl;

	std::istringstream	ss(line);
	std::string			key;
	std::string			value;

	std::getline(ss, key, ' ');
	std::getline(ss, value);
	
	key = trim(key);
	value = trim(value);

	if (key.length() != 0 || value.length() != 0) {
		_headers.insert(std::make_pair(key, value));
	}

}

/*
** using typedef on the map iterator to make it easier to read
*/
typedef std::map<std::string, std::string>::iterator MapIterator;
void	HttpRequest::_extractRequestLine() {

	for (MapIterator it = _headers.begin(); it != _headers.end(); it++) {

		// Checking if the first word of the line is a METHOD (enum requestMethod), NONE = 0
		if (isMethod(it->first)) {
			_method = isMethod(it->first);

			std::istringstream	ss(it->second);
			std::string			word;

			// Get the URI path
			std::getline(ss, word, ' ');
			_uriPath = word;

			// Get the HTTP version
			std::getline(ss, word, ' ');
			_httpVersion = word;

			// Removing request line from headers map
			_headers.erase(it);

			break ;
		}
	}
}

// Getters
std::string	HttpRequest::getMethod() {
	
	if (_method == GET) {
		return "GET";
	}
	else if (_method == POST) {
		return "POST";
	}
//	else if (_method == PUT) {
//		return "PUT";
//	}
	else if (_method == DELETE) {
		return "DELETE";
	}
//	else if (_method == OPTIONS) {
//		return "OPTIONS";
//	}
	else {
		return "NONE";
	}
}

std::string	HttpRequest::getUri() {
	return _uriPath;
}

std::string	HttpRequest::getHttpVersion() {
	return _httpVersion;
}

std::string	HttpRequest::getBodyBuffer() {
	return _bodyBuffer;
}

std::map<std::string, std::string>	HttpRequest::getHeaders() {
	return _headers;
}

/*
** Clean parsing helpers.
**
** `trim()` removes unnecessary spaces and new line characters etc.
*/
std::string	HttpRequest::trim(const std::string& str) {

	std::string	trimmed;

	trimmed = str;

	trimmed.erase(trimmed.find_last_not_of('\r') + 1);
	trimmed.erase(trimmed.find_last_not_of('\n') + 1);
	trimmed.erase(0, trimmed.find_first_not_of('\t'));
	trimmed.erase(trimmed.find_last_not_of('\t') + 1);
	trimmed.erase(0, trimmed.find_first_not_of(' '));
	trimmed.erase(trimmed.find_last_not_of(' ') + 1);
	trimmed.erase(trimmed.find_last_not_of(':') + 1);

	return trimmed;
}

Methods	HttpRequest::isMethod(const std::string& str) {

	if (str == "GET") {
		return GET;
	}
	else if (str == "POST") {
		return POST;
	} else  {
		return NONE;
	}
//	else if (str == "PUT") {
//		return PUT;
//	}
//	else if (str == "OPTIONS") {
//		return OPTIONS;
//	}
//	else {
//		return NONE;
//	}
}

void	HttpRequest::_printInHEX(char *buff, int len) {

	std::cout << "[";
	for (int i = 0; i < len; i++) {
		//std::cout << std::hex << (int)buff[i] << " ";
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buff[i] << " ";
	}
	std::cout << "]" << std::endl;
}

