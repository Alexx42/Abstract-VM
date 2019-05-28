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

bool			Parser::verify_type( std::string value ) {
	size_t index = value.find(' ');
	int		ok = 0;
	Error	err;
	if (index == std::string::npos)
	{
		err.setError("Bad number of argument");
		throw err;
	}
	std::string sub = value.substr(index + 1);
	size_t	index_p = sub.find('(');
	if (index_p == std::string::npos)
	{
		err.setError("Missing paarentheses");
		throw err;
	}
	std::string type = sub.substr(0, index_p);
	std::cout << type << std::endl;
	if (type == "int8")
		;
	else if (type == "int16")
		;
	else if (type == "int32")
		;
	else if (type == "float")
		;
	else if (type == "double")
		;
	else
	{
		err.setError("Invalid type\n");
		throw err;
	}
	size_t find_n = sub.find(')');
	// if (find_n == std::string::npos)
	// {
	// 	err.setError("Missing parentheses");
	// 	throw err;
	// }
	std::cout << "sub= " << sub << std::endl;
	std::string num = sub.substr(index_p + 1, find_n);
	std::cout << num << std::endl;
	std::istringstream tst(num);
	tst >> ok;
	if (!tst.good()) {
		std::cout << "OVERFKIW" << std::endl;
	}
	std::cout << ok << std::endl;
	return (0);
}

int 			Parser::verify_instruction( std::string line ) {
	std::size_t index = line.find(' ');
	std::string instr;
	Error err;

	err.setError("Bad instruction");
	if (index != std::string::npos)
		instr = line.substr(0, index);
	else
		instr = line;
	if (instr == "push")
		return (verify_type(line));
	if (instr == "assert")
		return (verify_type(line));
	if (instr == "pop")
		return (2);
	if (instr == "add")
		return (2);
	if (instr == "dump")
		return (2);
	if (instr == "mul")
		return (2);
	if (instr == "sub")
		return (2);
	if (instr == "div")
		return (2);
	if (instr == "mod")
		return (2);
	if (instr == "print")
		return (2);
	if (instr == "exit")
		return (3);
	throw err;
}



void			Parser::read_stdin( void ) {
	std::string line;
	for (; std::getline(std::cin, line);) {
		if (line == ";;")
			break ;
		try {
			verify_instruction(line);
		} catch (Error e) {
			std::cout << e.what() << std::endl;
		}
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