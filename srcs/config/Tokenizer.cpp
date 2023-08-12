/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:28:48 by athierry          #+#    #+#             */
/*   Updated: 2023/08/13 01:24:17 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tokenizer.hpp"

void Tokenizer::Tokenizer ( void ) {
}

void Tokenizer::Tokenizer ( Tokenizer & copy ) {
}

void Tokenizer::~Tokenizer ( void ) {
}

void Tokenizer::Tokenizer ( Tokenizer & copy ) {
}

bool Tokenizer::specialChar ( char c ) {
	return (c == '#' or c == '{' or c == '}' or c == ';' or c == '$');
}

void Tokenizer::charToken ( char c ) {
}

void Tokenizer::quotes ( std::string::iterator str ) {
}

void Tokenizer::token ( std::string::iterator str ) {
}

void Tokenizer::variable ( std::string::iterator str ) {
}

void Tokenizer::Tokenizer ( std::string & filename ) {
	std::ifstream	file(filename.c_str());
	if (!file)
		throw std::exception;
	std::string				content;
	std::string				line;
	while (std::getline(file, line)
		content.append(line + "\n");
	std::string::iterator	str;
	for (std::string::iterator str = content.begin(); str != content.end();){
		switch (*str){
			case '{':
				charToken(*(str++));
				break;
			case '}':
				charToken(*(str++));
				break;
			case ';':
				charToken(*(str++));
				break;
			case '\n':
				charToken(*(str++));
				break;
			case '\'':
				quotes(str);
				break;
			case '\"':
				quotes(str);
				break;
			case '$':
				variable(++str);
				break;
			case ' ':
				str++;
				break;
			case '\t':
				str++;
				break;
			case '\f':
				str++;
				break;
			case '\r':
				str++;
				break;
			case '\v':
				str++;
			case '#':
				while (str != content.end() and *(str++) != '\n')
					str++;
				break;
			default:
				token(str);
		}
	}
	
}

const std::string & Tokenizer::getToken ( void ){
}
