/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:00:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/01 00:32:51 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExecCommand.hpp"

int		ExecCommand::_ln = 1;

ExecCommand::ExecCommand( std::vector<std::pair<std::string, const IOperand *>> exec ) :
	_exec(exec)
{
	execFn[0] = {Add, 		{"add"}, 		&ExecCommand::add_s};
	execFn[1] = {Sub, 		{"sub"}, 		&ExecCommand::sub_s};
	execFn[2] = {Push, 		{"push"},		&ExecCommand::push_s};
	execFn[3] = {Mod, 		{"mod"}, 		&ExecCommand::mod_s};
	execFn[4] = {Mul, 		{"mul"}, 		&ExecCommand::mul_s};
	execFn[5] = {Assert, 	{"assert"}, 	&ExecCommand::assert_s};
	execFn[6] = {Print, 	{"print"}, 		&ExecCommand::print_s};
	execFn[7] = {Pop, 		{"pop"}, 		&ExecCommand::pop_s};
	execFn[8] = {Div, 		{"pop"}, 		&ExecCommand::pop_s};
	execFn[9] = {Dump, 		{"dump"}, 		&ExecCommand::dump_s};
	execFn[10] = {Exit, 	{"exit"}, 		&ExecCommand::exit_s};
}

ExecCommand::~ExecCommand( void )
	{;}

ExecCommand::ExecCommand(ExecCommand const & rhs) {
	*this = rhs;
}

ExecCommand & ExecCommand::operator=(ExecCommand const & rhs) {
	_exec = rhs._exec;
	return *this;
}

ExecCommand::ExecError::ExecError( std::string error, std::string type, int ln ) : Error(error, type, ln) {
	return ;
}

ExecCommand::ExecError::~ExecError( void ) {
	return ;
}

ExecCommand::ExecError::ExecError(ExecCommand::ExecError const & rhs) : Error(rhs) {
	static_cast<void>(rhs);
}

const	char		*ExecCommand::ExecError::what() const throw() {
	std::stringstream	ss;
	std::string			res;
	ss << "Line " << _ln << ": ";
	ss << _type << ": " << _error << std::endl;
	res = ss.str();
	return res.c_str();
}

ExecCommand::ExecError & ExecCommand::ExecError::operator=(ExecCommand::ExecError const & rhs) {
	static_cast<void>(rhs);
	return *this;
}

void		ExecCommand::push_s( const IOperand * rhs ) {
	_s.push_back(rhs);
}

void		ExecCommand::mul_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Stack size is less than 2", "Runtime error", _ln);
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	_s.push_back(*v1 * *v2);
}

void		ExecCommand::mod_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Stack size is less than 2", "Runtime error", _ln);
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	_s.push_back(*v1 % *v2);
}

void		ExecCommand::pop_s( IOperand const * rhs ) {

	static_cast<void>(rhs);
	if (_s.empty()) {
		throw ExecError("Stack is empty", "Runtime Error", _ln);
	} else { 
		_s.pop_back();
	}
}

void		ExecCommand::div_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Stack size is less than 2", "Runtime error", _ln);
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	_s.push_back(*v1 / *v2);
}

void		ExecCommand::sub_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Stack size is less than 2", "Runtime error", _ln);
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	_s.push_back(*v1 / *v2);
}

void		ExecCommand::add_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Stack size is less than 2", "Runtime error", _ln);
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	try {
		_s.push_back(*v1 + *v2);
	} catch (ExecError e) {
		throw ExecError("Overflow - Underflow", "Runtime Error", _ln);
	}
}

void		ExecCommand::print_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.back()->getType() != INT8 || _s.empty()) {
		throw ExecError("Top stack type is not int8", "Runtime error", _ln);
	} else {
		const char *pr = _s.back()->toString().c_str();
		std::cout << static_cast<char>(*pr) << std::endl;
	}
}

void		ExecCommand::assert_s( IOperand const * rhs ) {
	std::string		nb1;
	std::string		nb2;
	if (_s.empty() || !rhs) {
		throw ExecError("Assert failed", "Runtime Error", _ln);
	} else {
		nb1 = _s.back()->toString();
		nb2 = rhs->toString();
		if (nb1 != nb2) {
			throw ExecError("Assert failed", "Runtime Error", _ln);
		}
	}
}

void		ExecCommand::dump_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	std::vector< IOperand const *>::reverse_iterator it = _s.rbegin();

	for (; it != _s.rend(); it++) {
		std::cout << (*it)->toString() << std::endl;
	}
}

void		ExecCommand::exit_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
}

void		ExecCommand::execCommands( void ) {
	std::vector<std::pair<std::string, IOperand const *>>::iterator it;

	it = _exec.begin();
	while (it != _exec.end()) {
		for (int i = 0; i < Exit; i++) {
			if (execFn[i].e_val == it->first) {
				try {
					(*this.*execFn[i].fn)(it->second);
					break ;
				} catch (ExecError e) {
					std::cout << e.what() << std::endl;
					break ;
				}
			}
		}
		_ln++;
		it++;
	}
}