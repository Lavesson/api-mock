#include "responseserializer.h"
#include "responsedata.h"
#include <sstream>

std::string ApiMock::ResponseSerializer::statusCodeDescription(HTTP_RESPONSE_CODE responseCode) {
	switch (responseCode) {
	case HTTP_CONTINUE:							return "Continue";
	case HTTP_SWITCHING_PROTOCOLS:				return "Switching Protocols";
	case HTTP_OK:								return "OK";
	case HTTP_CREATED:							return "Created";
	case HTTP_ACCEPTED:							return "Accepted";
	case HTTP_NON_AUTHORATIVE_INFO:				return "Non-Authoritative Information";
	case HTTP_NO_CONTENT:						return "No Content";
	case HTTP_RESET_CONTENT:					return "Reset Content";
	case HTTP_PARTIAL_CONTENT:					return "Partial Content";
	case HTTP_MULTIPLE_CHOICES:					return "Multiple Choices";
	case HTTP_MOVED_PERMANENTLY:				return "Moved Permanently";
	case HTTP_FOUND:							return "Found";
	case HTTP_SEE_OTHER:						return "See Other";
	case HTTP_NOT_MODIFIED:						return "Not Modified";
	case HTTP_USE_PROXY:						return "Use Proxy";
	case HTTP_TEMPORARY_REDIRECT:				return "Temporary Redirect";
	case HTTP_BAD_REQUEST:						return "Bad Request";
	case HTTP_UNAUTHORIZED:						return "Unauthorized";
	case HTTP_FORBIDDEN:						return "Forbidden";
	case HTTP_NOT_FOUND:						return "Not Found";
	case HTTP_METHOD_NOT_ALLOWED:				return "Method Not Allowed";
	case HTTP_NOT_ACCEPTABLE:					return "Not Acceptable";
	case HTTP_PROXY_AUTH_REQUIRED:				return "Proxy Authentication Required";
	case HTTP_REQUEST_TIMEOUT:					return "Request Timeout";
	case HTTP_CONFLICT:							return "Conflict";
	case HTTP_GONE:								return "Gone";
	case HTTP_LENGTH_REQUIRED:					return "Length Required";
	case HTTP_PRECONDITION_FAILED:				return "Precondition Failed";
	case HTTP_REQUEST_ENTITY_TOO_LARGE:			return "Request Entity Too Large";
	case HTTP_REQUEST_URI_TOO_LONG:				return "Request-URI Too Long";
	case HTTP_UNSUPPORTED_MEDIA_TYPE:			return "Unsupported Media Type";
	case HTTP_REQUREST_RANGE_NOT_SATISFIABLE:	return "Requested Range Not Satisfiable";
	case HTTP_EXPECTATION_FAILED:				return "Expectation Failed";
	case HTTP_INTERNAL_SERVER_ERROR:			return "Internal Server Error";
	case HTTP_NOT_IMPLEMENTED:					return "Not Implemented";
	case HTTP_BAD_GATEWAY:						return "Bad Gateway";
	case HTTP_SERVICE_UNAVAILABLE:				return "Service Unavailable";
	case HTTP_GATEWAY_TIMEOUT:					return "Gateway Timeout";
	case HTTP_VERSION_NOT_SUPPORTED:			return "Version Not Supported";
	default:									return "";


	}
}

std::string ApiMock::ResponseSerializer::serialize(ResponseData response) {
	const std::string CRLF = "\r\n";
	std::stringstream ss;

	// Status line
	ss << "HTTP/1.1 ";
	ss << std::to_string(response.statusCode) << " " << statusCodeDescription(response.statusCode);
	ss << CRLF;
	
	// Response headers
	for (auto header : response.headers)
		ss << header.first << ": " << header.second << CRLF;

	// Body
	ss << CRLF;
	ss << response.body;

	auto r = ss.str();
	return r;
}