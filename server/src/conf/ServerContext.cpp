#include "ServerContext.hpp"

//::::::::::::::::::::::::::::::::::::::::::::::::::::CONSTRUCTORS / DESTRUCTORS

ServerContext::ServerContext() : AContext() {}

ServerContext::ServerContext(ServerContext const& rhs) : AContext() { *this = rhs; }

ServerContext& ServerContext::operator=(ServerContext const& rhs) { 

	if (this != &rhs) {
		
		this->_locations = rhs.getLocations();
		this->_listen = rhs.getListen();
		this->_serverNames = rhs.getServerNames();
	}
	return *this;
}

ServerContext::~ServerContext() {}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::GETTERS

std::map<std::string, int> const &			ServerContext::getListen(void) const { return this->_listen; }
std::map<std::string, std::string> const &	ServerContext::getLocations(void) const { return this->_locations; }
std::vector<std::string> const &			ServerContext::getServerNames(void) const { return this->_serverNames; }

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SETTERS

void	ServerContext::setListen(std::string const& ip, int port) { this->_listen[ip] = port; }
void	ServerContext::setLocation(std::string const& location, std::string const& root) { this->_locations[location] = root; }
void	ServerContext::setServerNames(std::vector<std::string> const& serverNames) { this->_serverNames = serverNames; }

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::METHODS

void ServerContext::_parseServerName(std::string const& line) {

	std::stringstream			stream(line);
	std::string					directive;
	std::string					serverName;
	std::vector<std::string> 	serverNames;

//	std::vector<std::string>::iterator it = AContext.getServerNames().begin();
//	if (*it == "localhost")
//		AContext.getServerNames().erase(it);
	
	stream >> directive;
	while (stream >> serverName) {
		if (serverName.find(';') != std::string::npos)
			serverName = serverName.substr(0, serverName.find_first_of(";"));
		serverNames.push_back(serverName);
	}
	this->setServerNames(serverNames);
}

void	ServerContext::_parseListen(std::string const& line) {

	std::stringstream	stream(line);
	std::string			listen;
	std::string			ip;
	int					port(80); //If only address is given, the port 80 is used.

//	std::map<std::string, int>::iterator it = this->_listen.begin();
//	if (it->first == "127.0.0.1" && it->second == 80)
//		this->_listen.erase(it);

//	TODO : check with defaut & possible values

	stream >> listen;
	if (stream.str().find(':') != std::string::npos)
	{
		std::getline(stream, ip, ':');
		if (ip.empty())
			ip = "127.0.0.1";
		ip = ip.substr(ip.find_first_not_of(" "), ip.size());
		this->isValidIPv4(ip);
	}
	stream >> port;
	this->setListen(ip, port);
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: OPERATOR OVERLOAD::

std::ostream &	operator<<(std::ostream & o, ServerContext const & sc) {

	o << HIPURPLE << std::setw(21) << "listen: " 			<< HIGREEN << print_map(sc.getListen()) 				<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "locations: " 		<< HIGREEN << print_map(sc.getLocations())				<< NO_COLOR << std::endl;
	o << HIPURPLE << std::setw(21) << "serverNames: " 		<< HIGREEN << print_vector(sc.getServerNames())			<< NO_COLOR << std::endl;

	return o;

}