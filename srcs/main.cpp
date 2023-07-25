/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:26:10 by athierry          #+#    #+#             */
/*   Updated: 2023/07/10 22:04:47 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "servr.hpp"

int	main ( int argc, char** argv ){
	if ( argc > 2 ){
		std::cout << "Too many arguments" << std::endl;
		return (1);
	}
	try {
		if (argc == 2)
			Servr	servr(*(argv + 1));
		else
			Servr	servr;

		servr.serve();
	}
	catch ( std::exception &e ){
		std::cerr << e.what() << std::endl;
		return (2);
	}
	return (0);
}
