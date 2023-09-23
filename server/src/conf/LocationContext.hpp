#ifndef LOCATION_CONTEXT_HPP
# define LOCATION_CONTEXT_HPP

#include "AContext.hpp"

class LocationContext : public AContext{

	public:
		LocationContext();
		LocationContext(LocationContext const&);
		LocationContext& operator=(LocationContext const& rhs);
		~LocationContext();

		void	setLocation(std::string const& location);
		void	setAlias(std::string const& alias);

		std::string const&	getLocation(void) const;
		std::string const&	getAlias(void) const;

	private:
		std::string		_location;
		std::string		_alias;
};

std::ostream &	operator<<(std::ostream & o, LocationContext const & cc);

#endif

/*IDEA : make templates func parser for common variables :
									- cgi
									- maxBodySize
									- root
									- errorPages
									- authorizedMethods
									- index
that would take an unknown class (ServerContext or LocationContext, parse, and call the setter)
*/