#ifndef SERVER_CONTEXT_HPP
# define SERVER_CONTEXT_HPP

# include "AContext.hpp"

class ServerContext : public AContext {

	public:
		ServerContext();
		ServerContext(ServerContext const&);
		ServerContext& operator=(ServerContext const& rhs);
		~ServerContext();

		std::map<std::string, int> const&			getListen(void) const;
		std::map<std::string, std::string> const&	getLocations() const;
		std::vector<std::string> const&				getServerNames(void) const;

		void	setListen(std::string const& ip, int port);
		void	setLocation(std::string const& location, std::string const& root);
		void	setServerNames(std::vector<std::string> const& serverNames);

	private:
		std::map<std::string, int> 			_listen; // <IP, port>
		std::map<std::string, std::string>	_locations; // TODO: change to map<string, LocationContext>		
		std::vector<std::string>			_serverNames;

};

std::ostream &	operator<<(std::ostream & o, ServerContext const & cc);

#endif
