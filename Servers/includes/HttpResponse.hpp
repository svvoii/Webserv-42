/*
** `HttpResponse` class responsible for generating the response
** to be sent back to the client/browser.
**
** This objetct is created on stack in the `_respond()` method of the
** `HttpServer` class, after the request is parsed by the `HttpRequest` class.
** 
** The `HttpRequest` object is passed to the constructor of this class
** via pointer upon construction.
*/
#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "HttpRequest.hpp"
#include <fstream>

#define INDEX_FILE_PATH "./www/index.html"
#define FAVICON_FILE_PATH "./www/favicon.ico"

enum HttpStatusCode {
	// Informational
	CONTINUE = 100,
	
	// Success
	OK = 200,
	CREATED = 201,
	ACCEPTED = 202,
	NO_CONTENT = 204,

	// Redirection
	MOVED_PERMANENTLY = 301,
	FOUND = 302,
	NOT_MODIFIED = 304,

	// Client Error
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	METHOD_NOT_ALLOWED = 405,

	// Server Error
	INTERNAL_SERVER_ERROR = 500,
	NOT_IMPLEMENTED = 501,
	BAD_GATEWAY = 502,
	SERVICE_UNAVAILABLE = 503
};

class HttpResponse {
	private:

		HttpRequest		*_httpRequest; // Pointer to the `HttpRequest` object, passed at construction
		std::string		_response; // To store the response to be sent back to the browser

		// This will map the request method to the corresponding response generator
		typedef void (HttpResponse::*ResponseGenerator)();
		std::map<enum requestMethod, ResponseGenerator>	_responseGenerators;

		void			_generateGetResponse();
		void			_generatePostResponse();
		void			_generatePutResponse();
		void			_generateDeleteResponse();
		void			_generateOptionsResponse();

		// Helpers
		void			_GetDefaultPath(std::ostringstream& responseStream);
		void			_GetFavicon(std::ostringstream& responseStream);
		void			_notFound(std::ostringstream& responseStream);
		std::string		_getFileContent(const std::string& filePath);

	public:

		HttpResponse(HttpRequest *httpRequest);
		~HttpResponse();

		std::string		getResponse();
};

#endif
