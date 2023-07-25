/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servr.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:25:26 by athierry          #+#    #+#             */
/*   Updated: 2023/07/24 23:00:34 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVR_HPP
#define SERVR_HPP

class 
class Connection{
	public:
		Connection ( void );
		Connection ( Connection& connection );
		~Connection ( void );
		Connection& operator = ( Connection& connection );
	private:
		int				FD;
};

class Socket{
	public:
		Socket ( void );
		Socket ( Socket& socket );
		~Socket ( void );
		Socket& operator = ( Socket& socket );
	private:
		int				FD;
		typedef struct Prmtr{
			std::string	host;
			int			port;
			int			max_connection;
		};
};

class Prmtr{
	public:
		Prmtr ( void );
		Prmtr ( Prmtr& prmtr );
		~Prmtr ( void );
		Prmtr& operator = ( Prmtr& prmtr );
	private:
};

class Servr{
	public:
		Servr ( void );
		Servr ( std::string& confFile );
		Servr ( Servr& servr );
		~Servr ( void );
		Servr& operator = ( Servr& servr );
		Serve ( void );
	private:
		std::vector<Socket>		_Sockets;
		std::vector<Connection>	_Connections;
		void	_init	( int port, char* host, int max_connection );
		void	_conf	( int fd_conf );
};

#endif
