/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:00:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/04 21:00:22 by ale-goff         ###   ########.fr       */
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
	execFn[8] = {Max, 		{"max"}, 		&ExecCommand::max_s};
	execFn[9] = {Min, 		{"min"}, 		&ExecCommand::min_s};
	execFn[10] = {Dump, 	{"dump"}, 		&ExecCommand::dump_s};
	execFn[11] = {Div, 		{"div"}, 		&ExecCommand::div_s};
	execFn[12] = {Exit, 	{"exit"}, 		&ExecCommand::exit_s};
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

ExecCommand::ExecError::ExecError( const std::string & error ) : Error(error) {
	return ;
}

ExecCommand::ExecError::~ExecError( void ) {
	return ;
}

ExecCommand::ExecError::ExecError(ExecCommand::ExecError const & rhs) : Error(rhs) {
	static_cast<void>(rhs);
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
		throw ExecError("Runtime Error : Stack size is less than 2");
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	_s.push_back(*v2 * *v1);
}

void		ExecCommand::mod_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Runtime Error : Stack size is less than 2");
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	_s.push_back(*v2 % *v1);
}

void		ExecCommand::pop_s( IOperand const * rhs ) {

	static_cast<void>(rhs);
	if (_s.empty()) {
		throw ExecError("Runtime Error : Stack is empty");
	} else { 
		_s.pop_back();
	}
}

void		ExecCommand::div_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Runtime Error : Stack size is less than 2");
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	std::cout << v1->toString() << std::endl;
	if (v1->toString() == "0") {
		throw ExecError("Runtime Error : Division by 0");
	}
	_s.pop_back();
	_s.push_back(*v2 / *v1);
}

void		ExecCommand::max_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	double		max;
	if (_s.size() < 1) {
		throw ExecError("Runtime Error : Stack is empty");
	}
	std::vector< const IOperand *>::iterator	it = _s.begin();
	max = std::stod((*it)->toString());
	while (it != _s.end())
	{
		if (std::stod((*it)->toString()) > max) {
			max = std::stod((*it)->toString());
		}
		it++;
	}
	std::cout << max << std::endl;
}

void		ExecCommand::min_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	double		min;
	if (_s.size() < 1) {
		throw ExecError("Runtime Error : Stack is empty");
	}
	std::vector< const IOperand *>::iterator	it = _s.begin();
	min = std::stod((*it)->toString());
	while (it != _s.end())
	{
		if (std::stod((*it)->toString()) < min) {
			min = std::stod((*it)->toString());
		}
		it++;
	}
	std::cout << min << std::endl;
}

void		ExecCommand::sub_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Runtime Error : Stack size is less than 2");
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	_s.push_back(*v2 / *v1);
}

void		ExecCommand::add_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.size() < 2) {
		throw ExecError("Runtime Error : Stack size is less than 2");
	}
	IOperand const *v1 = (_s.back());
	_s.pop_back();
	IOperand const *v2 = (_s.back());
	_s.pop_back();
	try {
		_s.push_back(*v2 + *v1);
	} catch (ExecError e) {
		throw ExecError("Runtime Error : Overflow - Underflow");
	}
}

void		ExecCommand::print_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	if (_s.back()->getType() != INT8 || _s.empty()) {
		throw ExecError("Runtime Error Top stack type is not int8");
	} else {
		const char *pr = _s.back()->toString().c_str();
		std::cout << static_cast<char>(std::atoi(pr)) << std::endl;
	}
}

void		ExecCommand::assert_s( IOperand const * rhs ) {
	std::string		nb1;
	std::string		nb2;
	if (_s.empty() || !rhs) {
		throw ExecError("Runtime Error : Assert failed");
	} else {
		nb1 = _s.back()->toString();
		nb2 = rhs->toString();
		if (nb1 != nb2) {
			throw ExecError("Runtime Error : Assert failed");
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
				} catch (ExecError & e) {
					std::cout << e.what() << std::endl;
					break ;
				}
			}
		}
		_ln++;
		it++;
	}
}