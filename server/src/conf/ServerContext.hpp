#ifndef SERVER_CONTEXT_HPP
# define SERVER_CONTEXT_HPP

#include "AContext.hpp"
#include "LocationContext.hpp"

class LocationContext;

class ServerContext : public AContext {

	public:
		ServerContext();
		ServerContext(ServerContext const&);
		ServerContext& operator=(ServerContext const& rhs);
		~ServerContext();

		std::map<std::string, int> const&				listen() const;
		std::map<std::string, LocationContext> const&	locations() const;
		std::vector<std::string> const&					serverNames() const;
		int												port() const;

		void	setListen(std::string const& ip, int port);
		void	addLocation(std::string const& location, LocationContext const& locationContext);
		void	setLocations(std::map<std::string, LocationContext> locationsMap);
		void	setServerNames(std::vector<std::string> const& serverNames);

		void	setDefaults();

	private:
		std::map<std::string, int> 				_listen;
		std::map<std::string, LocationContext>	_locations;
		std::vector<std::string>				_serverNames;

};

std::ostream &	operator<<(std::ostream & o, ServerContext const & cc);

#endif
