/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:56:10 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/01 00:41:30 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

int				Parser::_ln = 1;
#define ISSPACE(c) (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f')

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

void			Parser::removeZero( std::string & val ) {
	if (val.find('.') == std::string::npos) {
		return ;
	}
	for (std::string::size_type s = val.length() - 1; s > 0; --s) {
		if (val[s] == '0') {
			val.erase(s, 1);
		} else {
			break;
		}
	}
	if (val[val.length() - 1] == '.') {
		val.erase(val.length() - 1, 1);
	}
}

int				Parser::count_words( std::string str ) {
	int	count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ISSPACE(str[i]))
			i++;;
		if (str[i] && str[i] == ';') {
			return count;
		}
		if (str[i] && !ISSPACE(str[i]))
		{
			count++;
			while (str[i] && !ISSPACE(str[i]))
				i++;
		}
	}
	return (count);
}

void			Parser::isNumber( std::string str ) {
	int			count_dot;
	int			count_neg;

	count_dot = 0;
	count_neg = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] == ';') {
			throw ParserError(" ';' found near value", "Syntax Error", _ln);
		}
		if (!std::isdigit(str[i]) && str[i] != '.' && str[i] != '-')
			throw std::invalid_argument("");
		if (str[i] == '.') {
			count_dot++;
		} else if (str[i] == '-') {
			count_neg++;
		}
	}
	if (count_dot > 1 || count_neg > 1) {
		throw ParserError("Invalid value", "Syntax error", _ln);
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

Parser::ParserError::ParserError( std::string error, std::string type, int ln ) : Error(error, type, ln) {
	return ;
}

Parser::ParserError::~ParserError( void ) {
	return ;
}

Parser::ParserError::ParserError(Parser::ParserError const & rhs) : Error(rhs) {
	static_cast<void>(rhs);
}

Parser::ParserError & Parser::ParserError::operator=(Parser::ParserError const & rhs) {
	static_cast<void>(rhs);
	return *this;
}

const char *Parser::ParserError::what() const throw() {
	std::ostringstream	ss;
	std::string			res;
	ss << "Line " << _ln << ": ";
	ss << _type << ": " << _error << std::endl;
	res = ss.str();
	return res.c_str();
}

void			Parser::initVector( void ) {
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
	_type.push_back({"float", std::numeric_limits<float>::lowest(),  std::numeric_limits<float>::max()});
	_type.push_back({"double", std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()});

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
	std::string		str_p;
	double			nb;
	char			p_op;
	char			p_cl;
	str_p = extractString(val, '(', ')');
	if (str_p.empty()) {
		throw ParserError("Missing ')'", "Syntax Error", _ln);
	}
	p_op = 0;
	p_cl = 0;
	for (auto c : val) {
		if (!isspace(c) && p_cl > 0) {
			if (c == ';')
				break ;
			throw ParserError("after ')'", "Syntax Error", _ln);
		}
		if (c == '(')
			p_op++;
		else if (c == ')')
			p_cl++;
	}
	if (p_cl != 1 || p_op != 1) {
		throw ParserError("Invalid number of parentheses", "Syntax Error", _ln);
	}
	try {
		isNumber(str_p);
		nb = std::stod(str_p);
		std::string cmp = std::to_string(nb);
		removeZero(cmp);
		if (cmp != str_p) {
			if (str_p[0] == '-') {
				throw ParserError("Underflow", "Runtime Error", _ln);
			} else {
				throw ParserError("Overflow", "Runtime Error", _ln);
			}
		}
		if (nb > _type.at(e).max) {
			throw ParserError("Overflow", "Runtime Error", _ln);
		} else if (nb < _type.at(e).min) {
			throw ParserError("Underflow", "Runtime Error", _ln);
		}
	} catch (std::invalid_argument) {
		throw ParserError("Invalid value", "Syntax Error", _ln);
	}
	return (str_p);
}

IOperand		const *Parser::verify_type( std::vector<std::pair<std::string, bool>>::iterator it, std::string str ) {
	size_t					find_s;
	std::string				nb;
	eOperandType			e;
	CreateOperand			op;

	find_s = str.find(' ');
	if (count_words(str) != 1 + it->second)
	{
		std::cout << count_words(str);
		throw ParserError("Invalid number of arguments", "Syntax Error", _ln);
	}
	if (it->second == false)
		return nullptr;
	std::string type = extractString(str, ' ', '(');
	if (type.find(';') != std::string::npos) {
		throw ParserError("';' found near type", "Syntax Error", _ln);
	}
	type.erase(remove(type.begin(), type.end(), ' '), type.end()); 
	if (type.empty()) {
		throw ParserError("Missing '('", "Syntax Error", _ln);
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
		throw ParserError("Invalid type", "Syntax Error", _ln);
	}
	return (0);
}

std::vector<std::pair<std::string, bool>>::iterator Parser::verify_instruction( std::string line ) {
	std::size_t index = line.find(' ');
	std::string instr;

	if (index != std::string::npos)
		instr = line.substr(0, index);
	else
		instr = line;
	instr.erase(remove(instr.begin(), instr.end(), ' '), instr.end());
	for (std::vector<std::pair<std::string, bool>>::iterator it = _v.begin(); it != _v.end(); it++) {
		if ((it)->first == instr)
			return (it);
	}
	throw ParserError("Invalid instruction", "Syntax Error", _ln);
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
		ParserError err = _queueErr.front();
		std::cout << err.what() << std::endl;
		_queueErr.pop();
		is_err = true;
	}
	return is_err;
}

void			Parser::read_content( void ) {
	std::string		line;
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
		if (line.empty() ||  count == line.size() || line[0] == ';')
			continue ;
		try {
			auto it = verify_instruction(line);
			op = verify_type(it, line);
			_parse.push_back(std::make_pair(it->first, op));
			if (it->first == "exit") {
				_exit = true;
			}
		} catch (ParserError & e) {
			_queueErr.push(e);
		}
		_ln++;
	}
	// if (!_exit) {
	// 	_queueErr.push(ParserError("Missing Exit instruction", "Syntax error", -1));
	// }
	if (file.is_open())
		file.close();
}
