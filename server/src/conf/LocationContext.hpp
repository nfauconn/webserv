#ifndef LOCATION_CONTEXT_HPP
# define LOCATION_CONTEXT_HPP

#include "AContext.hpp"

class LocationContext : public AContext {

	public:
		LocationContext();
		LocationContext(LocationContext const&);
		LocationContext& operator=(LocationContext const& rhs);
		~LocationContext();

		std::string const&	alias() const;
		bool				isPyCgi() const;

		void				setAlias(std::string const& alias);
		void				setIsPyCgi(bool isPyCgi);

		void	setDefaults(void);
		
	private:
		std::string		_alias;
		bool			_isPyCgi;
};

std::ostream &	operator<<(std::ostream & o, LocationContext const & cc);

#endif