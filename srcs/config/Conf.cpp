/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:28:16 by athierry          #+#    #+#             */
/*   Updated: 2023/08/24 21:44:39 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conf.hpp"


Conf::Conf ( std::string & filename ): _Tokens(filename){

	std::string& token = _Tokens.getTocken();
	while (token != "" and token != "}"){
		t_checker	check = getIndex(token, depth);
		if (not check.possible)
			throw std::exception; // TODO
		if (check.
	}
}
