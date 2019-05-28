/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:56:10 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/27 23:04:16 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser( std::string str ) : _str(str) {
	choose_read();
	return ;
}

Parser::Parser( void ) {
	return ;
}

Parser::~Parser( void ) {
	return ;
}

Parser::Parser( Parser const & rhs ) {
	*this = rhs;
	return ;
}

Parser & Parser::operator=( Parser const & rhs ) {
	_str = rhs._str;
	return *this;
}

bool			Parser::verify_instructions( std::string _expr ) {
	
}


void			Parser::read_stdin( void ) {
	for (std::string line; std::getline(std::cin, line);) {
		if (line == ";;")
			break ;
		if (verify_instructions(s.substr(0, s.find('  '))))
			if (verify_type())
	}
}

void			Parser::read_file( void ) {
}	

void			Parser::choose_read( void ) {
	if (_str.empty())
		read_stdin();
	else
		read_file();
}