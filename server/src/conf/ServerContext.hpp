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

		bool											getAutoindex() const;
		std::map<std::string, int> const&				getListen(void) const;
		std::map<std::string, LocationContext> const&	getLocations() const;
		std::vector<std::string> const&					getServerNames(void) const;

		void	setAutoindex(bool autoindex);
		void	setListen(std::string const& ip, int port);
		void	addLocation(std::string const& location, LocationContext const& locationContext);
		void	setLocations(std::map<std::string, LocationContext> locationsMap);
		void	setServerNames(std::vector<std::string> const& serverNames);

	private:
		bool									_autoindex;
		std::map<std::string, int> 				_listen; // <IP, port>
		std::map<std::string, LocationContext>	_locations; // TODO: change to map<string, LocationContext>
		std::vector<std::string>				_serverNames;

};

std::ostream &	operator<<(std::ostream & o, ServerContext const & cc);

#endif
