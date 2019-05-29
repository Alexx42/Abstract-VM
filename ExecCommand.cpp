/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:00:03 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/29 03:57:18 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExecCommand.hpp"


ExecCommand::ExecCommand( std::vector<std::pair<std::string, const IOperand *>> exec ) :
	_exec(exec)
{
	execFn[0] = {Add, 		{"add"}, 		&ExecCommand::add_s};
	execFn[1] = {Sub, 		{"sub"}, 		&ExecCommand::sub_s};
	execFn[2] = {Push, 		{"push"},		&ExecCommand::push_s};
	execFn[3] = {Mod, 		{"mod"}, 		&ExecCommand::mod_s};
	execFn[4] = {Mul, 		{"mul"}, 		&ExecCommand::mul_s};
	execFn[5] = {Assert, 	{"assert"}, 	&ExecCommand::assert_s};
	execFn[6] = {Print, 	{"print"}, 	&ExecCommand::print_s};
	execFn[7] = {Pop, 		{"pop"}, 		&ExecCommand::pop_s};
	execFn[8] = {Div, 		{"pop"}, 		&ExecCommand::pop_s};
	execFn[9] = {Dump, 		{"dump"}, 	&ExecCommand::dump_s};
	execFn[10] = {Exit, 		{"exit"}, 	&ExecCommand::exit_s};
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

void		ExecCommand::push_s( const IOperand * rhs ) {
	_s.push_back(rhs);
}

void		ExecCommand::mul_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
}

void		ExecCommand::mod_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
}

void		ExecCommand::pop_s( IOperand const * rhs ) {
	Error err;

	static_cast<void>(rhs);
	if (_s.empty()) {
		err.setError("Stack is empty, nothing to pop");
		throw err;
	} else { 
		_s.pop_back();
	}
}

void		ExecCommand::div_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
}

void		ExecCommand::sub_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
}

void		ExecCommand::add_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
}

void		ExecCommand::print_s( IOperand const * rhs ) {
	static_cast<void>(rhs);
	Error		err;
	if (_s.back()->getType() != INT8 || _s.empty()) {
		err.setError("Top stack value is not an int8");
		throw err;
	} else {
		const char *pr = _s.back()->toString().c_str();
		std::cout << static_cast<char>(*pr) << std::endl;
	}
}

void		ExecCommand::assert_s( IOperand const * rhs ) {
	Error	err;
	std::string		nb1;
	std::string		nb2;
	err.setError("Instruction error : Assert failed");
	if (_s.empty() || !rhs) {
		throw err;
	} else {
		nb1 = _s.back()->toString();
		nb2 = rhs->toString();
		if (nb1 != nb2) {
			throw err;
		}
		throw err;
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
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			}
		}
		it++;
	}
}