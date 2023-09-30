#include "StatusLine.hpp"

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: CONSTRUCTORS::

StatusLine::StatusLine() : AResponse() {}

StatusLine::StatusLine(std::string const & path) : AResponse(path) {}

StatusLine::StatusLine(StatusLine const & rhs) : AResponse(rhs) {
	
	*this = rhs;
}

StatusLine::~StatusLine() {}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: OPERATORS::

StatusLine &		StatusLine::operator=(StatusLine const & rhs) {

	if (this != &rhs) {
		_message = rhs._message;
	}
	return *this;
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: ACCESSORS::

void				StatusLine::setStatusCode(int const & statusCode) { _statusCode = statusCode; }
int					StatusLine::getStatusCode() const { return _statusCode; }

void				StatusLine::setReasonPhrase(std::string const & reasonPhrase) { _reasonPhrase = reasonPhrase; }
std::string			StatusLine::getReasonPhrase() const { return _reasonPhrase; }

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: METHODS::

void				StatusLine::build() {

	std::stringstream statusLine;

	statusLine << "HTTP/1.1 ";
	statusLine << _statusCode << " ";
	statusLine << _reasonPhrase;
	statusLine << CRLF;

	this->setMessage(statusLine.str());
}
