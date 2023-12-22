#include "../includes/HttpResponse.hpp"
#include <sstream>


HttpResponse::HttpResponse(HttpRequest *httpRequest) 
	: _httpRequest(httpRequest), 
	_response("") {

	//std::cout << MAGENTA << "\tHttpResponse constructor called." << RESET << std::endl;

	_responseGenerators[GET] = &HttpResponse::_generateGetResponse;
	_responseGenerators[POST] = &HttpResponse::_generatePostResponse;
	_responseGenerators[PUT] = &HttpResponse::_generatePutResponse;
	_responseGenerators[DELETE] = &HttpResponse::_generateDeleteResponse;
	_responseGenerators[OPTIONS] = &HttpResponse::_generateOptionsResponse;

}

HttpResponse::~HttpResponse() {

	//std::cout << RED << "\t[~] HttpResponse destructor called." << RESET << std::endl;
}

void	HttpResponse::_generateGetResponse() {

	//std::cout << CYAN << "in _generateGetResponse()..\tpath:" << RESET << "[" << _httpRequest->getUri() << "]" << std::endl;
	std::ostringstream oss;

	if (_httpRequest->getUri() == "/") {
		_GetDefaultPath(oss);
	}
	else if (_httpRequest->getUri() == "/favicon.ico") {
		_GetFavicon(oss);
	}
	else {
		_notFound(oss);
	}

	_response = oss.str();

}

void	HttpResponse::_generatePostResponse() {

	//std::cout << CYAN << "in _generatePostResponse()..\tpath:" << RESET << "[" << _httpRequest->getUri() << "]" << std::endl;

	// TODO: Implement POST response
	// 201 Created
	_response = _httpRequest->getHttpVersion() + " ";
	std::stringstream ss;
	/*
	ss << CREATED;
	_response += ss.str() + " Created\r\n";
	_response += "Access-Control-Allow-Origin: *\r\n";
	_response += "Content-Type: text/html\r\n";
	_response += "\r\n";
	_response += "<html><body><h1>201 Created</h1></body></html>\r\n\r\n";
	*/
	// 200 OK
	/*
	ss << OK;
	_response += ss.str() + " OK\r\n";
	_response += "Access-Control-Allow-Origin: *\r\n";
	_response += "Content-Type: text/plain\r\n";
	_response += "\r\n";
	_response += "Hello from POST response! There is no spoon.\r\n\r\n";
	*/	
	ss << CREATED;
	_response += ss.str() + " Created\r\n";
	_response += "Access-Control-Allow-Origin: *\r\n";
	_response += "Content-Type: application/json\r\n";
	_response += "\r\n";
	_response += "{ \"id\": 1, \"title\": \"this is the title\", \"body\": \"this is the body\", \"userId\": 1 }\r\n\r\n";

}

void	HttpResponse::_generatePutResponse() {

	//std::cout << CYAN << "in _generatePutResponse()..\tpath:" << RESET << "[" << _httpRequest->getUri() << "]" << std::endl;

	// TODO: Implement PUT response
}

void	HttpResponse::_generateDeleteResponse() {

	//std::cout << CYAN << "in _generateDeleteResponse()..\tpath:" << RESET << "[" << _httpRequest->getUri() << "]" << std::endl;

	// TODO: Implement DELETE response
}

void	HttpResponse::_generateOptionsResponse() {

	//std::cout << CYAN << "in _generateOptionsResponse().." << RESET << std::endl;

	_response = _httpRequest->getHttpVersion() + " ";
	std::stringstream ss;
	ss << OK;
	_response += ss.str() + " OK\r\n";
	_response += "Access-Control-Allow-Origin: *\r\n";
	_response += "Access-Control-Allow-Methods: GET, POST, PUT, DELETE\r\n";
	_response += "Access-Control-Allow-Headers: Content-Type\r\n";
	_response += "Access-Control-Max-Age: 3600\r\n";
	_response += "Access-Control-Allow-Credentials: true\r\n";
	_response += "\r\n";

}

/*
** To generate the response, we retrieve the method from the `HttpRequest` 
** object and use it as a key to the `_responseGenerators` map, which will
** call the corresponding response generator method.
*/
std::string		HttpResponse::getResponse() {

	enum requestMethod	method = _httpRequest->isMethod(_httpRequest->getMethod());

	//std::cout << CYAN << "in getResponse().. method:[" << _httpRequest->getMethod() << "]" << RESET << std::endl;

	if (method != NONE) {
		(this->*_responseGenerators[method])();
	}

	return _response;
}

std::string		HttpResponse::_getFileContent(const std::string& filePath) {

	std::ifstream	file(filePath.c_str());
	
	if (file.is_open()) {

		std::string body((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		return body;
	}
	return "";
}

void	HttpResponse::_GetDefaultPath(std::ostringstream& responseStream) {

	std::string body = _getFileContent(INDEX_FILE_PATH);

	if (!body.empty()) {
		responseStream << _httpRequest->getHttpVersion() << " " << OK << " OK\r\n";
		responseStream << "Connection: close\r\n";
		responseStream << "Content-Length: " << body.length() << "\r\n";
		responseStream << "Content-Type: text/html\r\n";
		responseStream << "\r\n";
		responseStream << body << "\r\n\r\n";
	}
	else {
		_notFound(responseStream);
	}
}

void	HttpResponse::_GetFavicon(std::ostringstream& responseStream) {

	std::string body = _getFileContent(FAVICON_FILE_PATH);

	if (body.empty()) {
		responseStream << _httpRequest->getHttpVersion() << " " << OK << " OK\r\n";
		responseStream << "Connection: close\r\n";
		responseStream << "Content-Length: " << body.length() << "\r\n";
		responseStream << "Content-Type: image/x-icon\r\n";
		responseStream << "\r\n";
		responseStream << body << "\r\n\r\n";
	}
	else {
		_notFound(responseStream);
	}
}

void	HttpResponse::_notFound(std::ostringstream& responseStream) {

	std::string const body = "<html><body><h1>404 Not Found</h1></body></html>\r\n\r\n";

	responseStream << _httpRequest->getHttpVersion() << " ";
	responseStream << "404 Not Found\r\n";
	responseStream << "Connection: close\r\n";
	responseStream << "Content-Length: " << body.length() << "\r\n";
	responseStream << "Content-Type: text/html\r\n";
	responseStream << "\r\n";
	responseStream << body << "\r\n\r\n";
}
