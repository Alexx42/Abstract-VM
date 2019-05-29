/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:56:10 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/29 03:33:16 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

std::string		Parser::extractString( std::string source, char start, char end ) {
	std::size_t begPos;

	if ( (begPos = source.find(start)) != std::string::npos )
	{
		std::size_t endPos ;
		if ( (endPos = source.find(end, begPos)) != std::string::npos )
		{
			std::string result = source.substr(begPos+1, endPos-begPos-1) ;
			return result ;
		}
	}
	return std::string() ;
}

int				Parser::count_words( std::string str ) {
	bool inSpaces = true;
	int numWords = 0;
	int i = 0;;
	while (str[i])
	{
		while (str[i] && std::isspace(str[i]))
		{
			inSpaces = true;
			i++;
		}
		if (!str[i])
			break ;
		if (inSpaces)
		{
			numWords++;
			inSpaces = false;
		}
		if (str[i])
			i++;
	}
	return numWords;
}

void			Parser::isNumber( std::string str ) {
	for (int i = 0; str[i]; i++) {
		if (!std::isdigit(str[i]))
			throw std::invalid_argument("");
	}
}

Parser::Parser( std::string str ) : _str(str) {
	
	return ;
}

Parser::Parser( void ) {
	initVector();
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

void			Parser::initVector( void ) {
	//TODO
	_v.push_back(std::make_pair("push", true));
	_v.push_back(std::make_pair("pop", false));
	_v.push_back(std::make_pair("assert", true));
	_v.push_back(std::make_pair("dump", false));
	_v.push_back(std::make_pair("mul", false));
	_v.push_back(std::make_pair("div", false));
	_v.push_back(std::make_pair("add", false));
	_v.push_back(std::make_pair("sub", false));
	_v.push_back(std::make_pair("print", false));
	_v.push_back(std::make_pair("exit", false));
	_v.push_back(std::make_pair("mod", false));

	_type.push_back({"int8", INT8_MIN, INT8_MAX});
	_type.push_back({"int16", INT16_MIN, INT16_MAX});
	_type.push_back({"int32", INT32_MIN, INT32_MAX});
	_type.push_back({"float", __FLT_MIN__, __FLT_MAX__});
	_type.push_back({"double", __DBL_MIN__, __DBL_MAX__});

}

std::vector<std::pair<std::string, const IOperand *>> & Parser::getParse() {
	return _parse;
}

eOperandType		Parser::getEnumValue( std::string type ) {
	if (type == "int8")
		return INT8;
	else if (type == "int16")
		return INT16;
	else if (type == "int32")
		return INT32;
	else if (type == "float")
		return FLOAT;
	else
		return DOUBLE;
}


std::string		Parser::verify_value( std::string val, eOperandType e ) {
	Error			err;
	std::string		str_p;
	double			nb;
	char			p_op;
	char			p_cl;
	str_p = extractString(val, '(', ')');
	if (str_p.empty()) {
		err.setError("Missing ')'");
		throw err;
	}
	p_op = 0;
	p_cl = 0;
	for (auto c : val) {
		if (!isspace(c) && p_cl > 0) {
			err.setError("Syntax error after ')'");
			throw err;
		}
		if (c == '(')
			p_op++;
		else if (c == ')')
			p_cl++;
	}
	if (p_cl != 1 || p_op != 1) {
		err.setError("Invalid number of parentheses");
		throw err;
	}
	try {
		isNumber(str_p);
		nb = std::stoi(str_p);
		if (nb > _type.at(e).max) {
			err.setError("Overflow");
			throw err;
		} else if (nb < _type.at(e).min) {
			err.setError("Underflow");
			throw err;
		}
	} catch (std::out_of_range e) {
		err.setError(e.what());
		throw err;
	} catch (std::invalid_argument) {
		err.setError("Invalid value");
		throw err;
	}
	return (str_p);
}

IOperand		const *Parser::verify_type( std::vector<std::pair<std::string, bool>>::iterator it, std::string str ) {
	Error					err;
	size_t					find_s;
	std::string				nb;
	eOperandType			e;
	CreateOperand			op;

	find_s = str.find(' ');
	if (count_words(str) != 1 + it->second || (find_s != std::string::npos && it->second == false) || (find_s == std::string::npos && it->second == true))
	{
		err.setError("Wrong number of arguments");
		throw err;
	}
	if (it->second == false)
		return nullptr;
	std::string type = extractString(str, ' ', '(');
	type.erase(remove(type.begin(), type.end(), ' '), type.end()); 
	if (type.empty()) {
		err.setError("Missing '('");
		throw err;
	}
	std::vector<Infos>::iterator it_type = _type.begin();
	for (; it_type != _type.end(); it_type++) {
		if (type == it_type->type) {
			e = getEnumValue( type );
			nb = verify_value( str, e );
			return op.createOperand(e, nb);
		}
	}
	if (it_type == _type.end()) {
		err.setError("Invalid type");
		throw err;
	}
	return (0);
}

std::vector<std::pair<std::string, bool>>::iterator Parser::verify_instruction( std::string line ) {
	std::size_t index = line.find(' ');
	std::string instr;
	Error 		err;

	if (index != std::string::npos)
		instr = line.substr(0, index);
	else
		instr = line;
	for (std::vector<std::pair<std::string, bool>>::iterator it = _v.begin(); it != _v.end(); it++) {
		if ((it)->first == instr)
			return (it);
	}
	err.setError("Bad instruction");
	throw err;
}


void			Parser::printParse( void ) {
	std::vector<std::pair<std::string, const IOperand*>>::iterator it;

	it = _parse.begin();
	while (it != _parse.end()) {
		std::cout << "------LINE------" << std::endl;
		std::cout << "{" << it->first << "}	";
		if (it->second)
			std::cout << "{" << it->second->toString() << "}" << std::endl;
		else
			std::cout << std::endl;
		it++;
	}
}

bool		Parser::printError( void ) {
	bool		is_err;

	is_err = false;
	while (!_queueErr.empty()) {
		Error err = _queueErr.front();
		std::cout << err.what() << std::endl;
		_queueErr.pop();
		is_err = true;
	}
	return is_err;
}

void			Parser::read_content( void ) {
	std::string		line;
	Error			err;
	IOperand const	*op;
	std::ifstream	file;
	bool			_exit;

	if (!_str.empty()) {
		file.open(_str);
	}
	_exit = false;
	for (; std::getline(_str.empty() ? std::cin : file, line);) {
		if (line == ";;")
			break ;
		size_t count =  static_cast<size_t>(std::count(line.begin(), line.end(), ' '));
		if (line.empty() ||  count == line.size())
			continue ;
		try {
			auto it = verify_instruction(line);
			op = verify_type(it, line);
			_parse.push_back(std::make_pair(it->first, op));
			if (it->first == "exit") {
				_exit = true;
				break ;
			}
		} catch (Error e) {
			_queueErr.push(e);
		}
	}
	if (!_exit) {
		err.setError("No exit instruction");
		_queueErr.push(err);
	}
	if (file.is_open())
		file.close();
}
