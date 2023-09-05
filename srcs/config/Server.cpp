/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 22:54:55 by athierry          #+#    #+#             */
/*   Updated: 2023/09/05 23:59:24 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server ( void ){
}

Server::Server ( Server & copy ): _Name(copy._Name), _Directives(copy._Directives){
}

Server::~Server ( void ){
}

Server & Server::operator = ( Server & copy ){
	_Name = copy._Name;
	_Directives = copy._Directives;
	return (*this);
}

Server::Server ( std::string & name ): _Name(name){
}

void Server::addDirective ( std::string name, Tokenizer& tokens){
	std::vector < std::string >	values;
	int							i;

	if (_Directives.count(name))
		throw std::exception(); // TODO Directive already exists
	for (i = 0; i < KEYWORDS; i++)
		if (_Checker[i].name == name)
			break;
	if (i == KEYWORDS)
		throw std::exception() // TODO No such directive in context
	values.push_back(tokens.getToken());
	if (_Checker[i].multiple)
	
}

std::vector<std::string> Server::getDirective( std::string name ){
}
