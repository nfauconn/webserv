/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:07:18 by athierry          #+#    #+#             */
/*   Updated: 2023/08/09 00:21:57 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

class Context: public class Bloc{
	public:
		Context ( void );
		Context ( Context & bloc );
		~Context ( void );
		Context & operator = ( Context & bloc );
	protected:
		std::map < std::string, Bloc>	_Blocs;
	private:
};

#endif
