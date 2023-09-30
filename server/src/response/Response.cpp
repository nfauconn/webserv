#include "Response.hpp"

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: CONSTRUCTORS::

Response::Response() : AReponse(), _method(NULL) {}

Response::Response(Request const & request, ServerContext const & serverContext) : _method(NULL) {

}

Response::Response(Response const & rhs) : AResponse(rhs) {
	
	*this = rhs;
}

Response::~Response() {}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: OPERATORS::

Response &		Response::operator=(Response const & rhs) {

	if (this != &rhs) {
		this->setMethod(rhs.getMethod());
		this->setStatusLine(rhs.getStatusLine());
		this->setHeaders(rhs.getHeaders());
		this->setBody(rhs.getBody());
	}

	return *this;
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: ACCESSORS::

void			Response::setMethod(AHandler * method) { _method = method; }
void			Response::setStatusLine(StatusLine const & statusLine) { _statusLine = statusLine; }
void			Response::setHeaders(Headers const & headers) { _headers = headers; }
void			Response::setBody(Body const & body) { _body = body; }

AHandler *		Response::getMethod() const { return _method; }
StatusLine		Response::getStatusLine() const { return _statusLine; }
Headers			Response::getHeaders() const { return _headers; }
Body			Response::getBody() const { return _body; }

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: METHODS::

void			Response::build() {

	this->_method->handle();
	
	this->_statusLine.build();
	
	this->_body.build();

	this->_headers.setContentLength(_body.getMessage().length());
	this->_headers.build();

	this->setMessage(_statusLine.getMessage() + _headers.getMessage() + _body.getMessage());
}
