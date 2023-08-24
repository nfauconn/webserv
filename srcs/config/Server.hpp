/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:07:18 by athierry          #+#    #+#             */
/*   Updated: 2023/08/24 23:42:16 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

class Server{
	public:
		// Coplien Compliant
		Server ( void );
		Server ( Server & copy );
		~Server ( void );
		Server & operator = ( Server & copy );
		// Constructor
		Server ( std::string & name );
		// 
		typedef std::map < std::string, std::vector < std::string > >	Directives;
		// 
	protected:
	private:
		std::string		_Name;
		Directives		_Directives;
};

#endif
