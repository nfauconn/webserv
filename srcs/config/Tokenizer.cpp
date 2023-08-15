/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:28:48 by athierry          #+#    #+#             */
/*   Updated: 2023/08/15 20:30:44 by athierry         ###   ########.fr       */
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
	std::string content;
	content += c;
	_Tokens.push_back(content);
}

void Tokenizer::quotes ( std::string::iterator & str ) {
	std::string	content;
	char		c = *str++;
	while (*str && *str != c) {
		content += *str;
		str++;
		}
	if (*str == c)
		str++;
	_Tokens.push_back(content);
}

void Tokenizer::variable ( std::string::iterator& str ) {
	// TODO
	token(str);
}

void Tokenizer::spaces ( std::string::iterator & str ) {
	while (*str and std::isspace(*str))
		str++;
}

void Tokenizer::token ( std::string::iterator & str ) {
	std::string content;
	while (*str and not std::isspace(*str) and not specialChar(*str)){
		content += *str;
		str++;
	}
	_Tokens.push_back(content);
}

void Tokenizer::variable ( std::string::iterator & str ) {
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
			case '}':
			case ';':
			case '\n':
				charToken(*(str++));
				break;
			case '\'':
			case '\"':
				quotes(str);
				break;
			case '$':
				variable(++str);
				break;
			case ' ':
			case '\t':
			case '\f':
			case '\r':
			case '\v':
				spaces(str);
				break;
			case '#':
				comment(++str);
				break;
			default:
				token(str);
		}
	}
	
}

const std::string & Tokenizer::getToken ( void ){
	const std::string		end = "";
	static TokenIterator	iterator = _Tokens.begin();

	if (iterator == _Tokens.end())
		return end;
	return (*(iterator++));
}
