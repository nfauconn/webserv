#include "LocationContext.hpp"

LocationContext::LocationContext() : AContext(), _location(""), _alias("") {}

LocationContext::LocationContext(LocationContext const& rhs) { *this = rhs; }

LocationContext& LocationContext::operator=(LocationContext const& rhs) { 

	if (this != &rhs) {
		
		this->_location = rhs.getLocation();
		this->_alias = rhs.getAlias();
	}
	return *this;
}

LocationContext::~LocationContext() {}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::GETTERS

std::string const&	LocationContext::getLocation(void) const { return this->_location; }
std::string const&	LocationContext::getAlias(void) const { return this->_alias; }

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SETTERS

void	LocationContext::setLocation(std::string const& location) { this->_location = location; }
void	LocationContext::setAlias(std::string const& alias) { this->_alias = alias; }

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::METHODS


// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: OPERATOR OVERLOAD::

std::ostream &	operator<<(std::ostream & o, LocationContext const & sc) {

	o << HIPURPLE << std::setw(21) << "LocationContext : "	<< NO_COLOR << std::endl;

	o << HIPURPLE << std::setw(21) << "location : " << HIGREEN << sc.getLocation() 	<< NO_COLOR << std::endl;	
	o << HIPURPLE << std::setw(21) << "alias : " 	<< HIGREEN << sc.getAlias() 	<< NO_COLOR << std::endl;
	return o;
}