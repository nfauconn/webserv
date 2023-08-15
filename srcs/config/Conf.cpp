/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:28:16 by athierry          #+#    #+#             */
/*   Updated: 2023/08/16 00:04:06 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Conf.hpp"


Conf::Conf ( std::string & filename ): _Tokens(filename){

	std::string& token = tokens.getTocken();
	while (token != "" and token != "}"){
		t_checker	check = getIndex(token, depth);
		if (not check.possible)
			throw std::exception; // TODO
		if (check.
	}
}
