/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:28:56 by athierry          #+#    #+#             */
/*   Updated: 2023/08/15 20:30:44 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

class Tokenizer{
	public:
		// Coplien Compliant
		Tokenizer ( void );
		Tokenizer ( Tokenizer & copy );
		~Tokenizer ( void );
		Tokenizer & operator = ( Tokenizer & copy );
		// 
		typedef	std::vector < std::string >		TokenContainer;
		typedef TokenContainer::const_iterator	TokenIterator;
		//
		Tokenizer ( std::string & filename );
		const std::string & getToken ( void );
	protected:
	private:
		TokenContainer						_Tokens;
		void	token( std::string::iterator& str );
		void	spaces( std::string::iterator& str );
		void	variable( std::string::iterator& str );
		void	quotes( std::string::iterator& str );
		void	comment( std::string::iterator& str );
		bool	charToken( char c );
};

#endif
