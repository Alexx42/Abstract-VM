/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateOperand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:16:44 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/30 23:42:06 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateOperand.hpp"
#include "Operand.hpp"

CreateOperand::CreateOperand( void ) {
	return ;
}

CreateOperand::~CreateOperand( void ) {
	return ;
}

CreateOperand::CreateOperand(CreateOperand const & rhs) {
	*this = rhs;
	return ;
}

CreateOperand & CreateOperand::operator=(CreateOperand const & rhs) {
	static_cast<void>(rhs);
	return (*this);
}

IOperand const *CreateOperand::createInt8( std::string const & value ) const {
	IOperand *op = new Operand<int8_t>(value, 0, INT8);
	return (op);
}

IOperand const *CreateOperand::createInt16( std::string const & value ) const {
	IOperand *op = new Operand<int16_t>(value, 0, INT16);
	return (op);
}

IOperand const *CreateOperand::createInt32( std::string const & value ) const {
	IOperand *op = new Operand<int32_t>(value, 0, INT32);
	return (op);
}

IOperand const *CreateOperand::createFloat( std::string const & value ) const {
	int		precision;

	precision = 0;
	if (value.find('.') != std::string::npos) {
		for (std::string::size_type s = value.length() - 1; s > 0 && value[s] != '.'; s--) {
			precision++;
		}
	}
	IOperand *op = new Operand<float>(value, precision, FLOAT);
	return (op);
}

IOperand const *CreateOperand::createDouble( std::string const & value ) const {
	int		precision;

	precision = 0;
	if (value.find('.') != std::string::npos) {
		for (std::string::size_type s = value.length() - 1; s > 0 && value[s] != '.'; s--) {
			precision++;
		}
	}
	IOperand *op = new Operand<double>(value, precision, DOUBLE);
	return (op);
}

IOperand const	*CreateOperand::createOperand( eOperandType e, std::string const & value ) const {
	return disp.at(e)(value);
}