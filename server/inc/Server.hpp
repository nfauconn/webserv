#ifndef SERVER_HPP
# define SERVER_HPP

# define DEBUG

#include <iostream>
#include <map>

#include "Config.hpp"
#include "Epoll.hpp"
#include "Request.hpp"

typedef std::map<int, Request>				clientData_t;

class Server {

	public:

		Server();
		Server(std::string const& conf_file);
		Server(Server const& rhs);
		~Server();
		Server& operator=(Server const& rhs);

		Config const&		getConfig() const;
		Epoll const&		getEpollEvents() const;

		void				connect();

	private:

		Config								_config;
		Epoll								_epollEvents;
		clientData_t						_clientsData;

		void								_readFromClient(int clientFd);
		void								_writeToClient(int clientFd);
		bool								_isRequestEnded(int clientFd);
		void								_handleClientData(int clientFd);
		void								_endClientConnexion(int clientFd);

};

#endif
