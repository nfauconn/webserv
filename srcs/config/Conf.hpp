/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:28:22 by athierry          #+#    #+#             */
/*   Updated: 2023/09/05 22:54:39 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP

class Conf{
	public:
		// Coplien Compliant
		Conf ( void );
		Conf ( Conf & copy );
		~Conf ( void );
		Conf & operator = ( Conf & copy );
		// Constructor
		Conf ( std::string & filename );
		// 
		// 
	protected:
		// 
	private:
		// 
		Tokenizer					_Tokens;
		std::vector<Server>		_Servers;
		// 
};

#endif
