/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servr.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:26:50 by athierry          #+#    #+#             */
/*   Updated: 2023/07/24 23:00:34 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "servr.hpp"

void Servr::_Init( int port, char *host, int max_connextion ){
	struct sockadress_in	address;
	int						addressLengh = sizeof(address);

	for (std::vector<Server>::iterator it = _Servers.begin(); it != _Servers.end(); it++){
		if ((it.FD = socket(AF_INET, SOCK_STREAM, 0)) == 0){
			std::cerr << "Couldn't open main socket" << std::endl:
			throw
		}
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons( it.prmtr.port );

		memset(address.sin_zero, '\0',sizeof address.sin_zero);

		if (bind(it.FD, (struct sockaddr *)&address, sizeof(address)) < 0){
			std::cerr << "Couldn't bind main socket" << std::endl;
			throw
		}

		if (listen(it.FD, it.prmtr.max_connection) < 0){
			std::cerr << "Couldn't listen to main socket" << std::endl;
			throw
		}
	}
}

Servr::Servr ( void ): _FEServr( 0 ), _Set( false ){
	int		port = 8080;	
	char*	host = "sna.fr";
	int		max_connection = 10;

	_Init(port, host, max_connection);
}

Servr::Servr ( std::string& confFile ): _FEServr( 0 ), _Set( false ){
	int fd_conf = open(conFile);
	_conf( fd_conf );
}

Servr::Servr ( Servr& servr ): _FDServr( servr._FDServr ), _Set( servr._Set ), _Prmtr( servr._Prmtr ){
}

Servr::~Servr ( void ){
	close( _FDServer );
}

Servr& Servr::operator = ( Servr& servr ){
	if (_Set)
		close( _FDServer );
	_FDServr = servr._FDServr;
	_Set = servr._Set;
	__Prmtr = servr.__Prmtr;
	return( *this );
}

Servr::Serve ( void ){
}
