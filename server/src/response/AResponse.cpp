#include "AResponse.hpp"

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: CONSTRUCTORS::

AResponse::AResponse() {}

AResponse::AResponse(std::string const & path) {}

AResponse::AResponse(AResponse const & src) {
	*this = src;
}

AResponse::~AResponse() {}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: OPERATORS::

AResponse &		AResponse::operator=(AResponse const & rhs) {

	if (this != &rhs) {
		_message = rhs._message;
	}
	return *this;
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: ACCESSORS::

void			AResponse::setMessage(std::string const & message) { _message = message; }

std::string		AResponse::getMessage() const { return _message; }