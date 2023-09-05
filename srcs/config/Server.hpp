/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:07:18 by athierry          #+#    #+#             */
/*   Updated: 2023/09/05 23:20:57 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Checker.hpp"

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
		void						addDirective ( std::string name, Tokenizer& tokens);
		std::vector < std::string >	getDirective( std::string name );
	protected:
	private:
		std::string				_Name;
		Directives				_Directives;
		t_checker[KEYWORDS]&	_Checker;
};

#endif
