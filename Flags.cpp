/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 20:44:50 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/02 21:32:21 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Flags.hpp"

Flags::Flags( char **str ) : _str(str), _h(0), _d(0), _nbFlags(0) {
	return ;
}

Flags::~Flags( void ) {
	return ;
}

Flags::Flags(Flags const & rhs) {
	static_cast<void>(rhs);
}

Flags & Flags::operator=(Flags const & rhs) {
	static_cast<void>(rhs);
	return *this;
}

void		Flags::printHelp( void ) {
	std::cout << "usage: ./avm [-opt] [stdin] | [file]" << std::endl;
	std::cout << "Version: 1.0" << std::endl;
	std::cout << "Author:	Alexandre Le Goff\n" << std::endl;
	std::cout << "Options: " << std::endl;
	std::cout << "-h:		Print help for the program" << std::endl;
	std::cout << "-d:		Debugger" << std::endl;
}

int			Flags::getNbFlags( void ) {
	return _nbFlags;
}

int			Flags::getDebug( void ) {
	return _d;
}

void		Flags::parserStr( void ) {
	int		i;
	int 	j;

	i = 1;
	while (_str && _str[i])
	{
		j = 1;
		if (_str[i][0] == '-') {
			while (_str[i][j]) {
				if (_str[i][j] == 'h') {
					_h = 1;
					_nbFlags++;
					j++;
				}
				if (_str[i][j] == 'd') {
					_d = 1;
					_nbFlags++;
					j++;
				}
				if (_str[i][j])
					j++;
			}
		} else {
			break ;
		}
		i++;
	}
	if (_h == 1) {
		printHelp();
		exit(0);
	}
}