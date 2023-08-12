/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:20:00 by athierry          #+#    #+#             */
/*   Updated: 2023/08/10 21:07:45 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTIVE_HPP
# define DIRECTIVE_HPP

class Directive{
	public:
		// Coplien Compliant
		Directive ( void );
		Directive ( Directive & copy );
		~Directive ( void );
		Directive & operator = ( Directive & copy );
		// Constructor
	protected:
	private:
		std::string															_pName;
		std::string															_pParent;
		std::map < std::string, std::vector < std::string > >				_pDirectives;
};

#endif
