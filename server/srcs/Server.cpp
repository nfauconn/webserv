#include "../inc/Server.hpp"

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::CONSTRUCTORS / DESTRUCTORS

Server::Server() :	_config(), 
					_epollEvents(this->_config.getPorts()) {
}

Server::Server(std::string const& conf_file) :	_config(conf_file), 
												_epollEvents(this->_config.getPorts()) {
}

Server::Server(Server const& rhs) {

	*this = rhs;
}

Server::~Server() {

	// TODO
}


Server& Server::operator=(Server const& rhs) {

	if (this != &rhs) {
        // TODO
	}
	return *this;
}


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::GETTERS / SETTERS

Config const&	Server::getConfig() const { return this->_config; }

Epoll const&	Server::getEpollEvents() const { return this->_epollEvents; }


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MEMBER FUNCTIONS


void	Server::connect() {

	struct epoll_event	event;
	int					nb_events;
	int					clientFd;

	try {

		while (true) {

			nb_events = this->_epollEvents.waitForConnexions();
			for (int i = 0; i < nb_events; ++i) {

				event = this->_epollEvents.getReadyEvent(i);
				clientFd = event.data.fd;
				if ((event.events & EPOLLERR) ||(event.events & EPOLLHUP)) {
					log(clientFd, "Epoll error");
					_endClientConnexion(clientFd);
				}
				else if (event.events & EPOLLRDHUP) {
					log(clientFd, "Closed connexion");
					_endClientConnexion(clientFd);
				}
				else if (this->_epollEvents.isNewClient(clientFd)) {
					this->_epollEvents.addNewClient(clientFd);
				}
				else if (event.events & EPOLLIN) {
					_readFromClient(clientFd);
				}
				else if (event.events & EPOLLOUT) {
					_writeToClient(clientFd);
				}
			}
		}
	}
	catch (std::exception& e) {

		std::cerr << "ERROR: " << e.what() << std::endl;
	}
}

void	Server::_readFromClient(int clientFd) {

	std::vector<char>	buffer(BUFFER_SIZE, '\0');

	int	bytesRead = recv(clientFd, &buffer[0], buffer.size(), 0);
	if (bytesRead < 0) {
		throw std::runtime_error(RECVERR);
	}
	else if (bytesRead == 0) { 
		log(clientFd, "End of connexion");
		_endClientConnexion(clientFd);
	}
	else {
		buffer.resize(bytesRead);
	}
	this->_clientData[clientFd].insert(this->_clientData[clientFd].end(), buffer.begin(), buffer.end());
	_handleClientData(clientFd);
}

void	Server::_writeToClient(int clientFd) {

	std::string message = "Request received";
	if ((send(clientFd, message.c_str(), message.length(), 0)) < 0) {
		throw std::runtime_error(SENDERR);
	}
	_endClientConnexion(clientFd);
}


void	Server::_handleClientData(int clientFd) {

	if (!_isRequestEnded(clientFd))
		return ;

	std::string str;
	str.assign(&this->_clientData[clientFd][0]);
	#ifdef DEBUG
	std::cout << &this->_clientData[clientFd][0] << std::endl;
	#endif
	this->_clientRequest.parser(str);
	// try catch d'exceptions ? (mauvaise requete)
	this->_epollEvents.editSocketInEpoll(clientFd, EPOLLOUT);
}

bool	Server::_isRequestEnded(int clientFd) {

	std::string	end_of_data(&this->_clientData[clientFd].end()[-4], &this->_clientData[clientFd].end()[0]);

	if (this->_clientData[clientFd].size() > 4 && end_of_data == DB_CRLF)
	{
		std::string	last_buffer(&this->_clientData[clientFd].end()[-100], &this->_clientData[clientFd].end()[0]);
		if (last_buffer.find("Content-Length") != std::string::npos)
		{
			std::cout << "Last buffer: \n" << last_buffer << std::endl;
			std::cout << "Content-Length found" << std::endl;
			//handle body size
			return false;
		}
	 	return true;
	}
	return false;
}

void	Server::_endClientConnexion(int clientFd) {

	this->_clientData.erase(clientFd);
	close(clientFd);
}
