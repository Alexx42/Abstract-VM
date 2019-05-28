/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:10:39 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/27 18:27:49 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include <iostream>
#include <string>

enum eOperandType{
	Int8, Int16, Int32, Float, Double
};

class IOperand
{
	public:
		virtual int				getPrecision( void ) const = 0;
		virtual eOperandType	getType( void ) const = 0;

		virtual IOperand const * operator+(IOperand const & rhs) const = 0;
		virtual IOperand const * operator-(IOperand const & rhs) const = 0;
		virtual IOperand const * operator*(IOperand const & rhs) const = 0;
		virtual IOperand const * operator/(IOperand const & rhs) const = 0;
		virtual IOperand const * operator%(IOperand const & rhs) const = 0;

		virtual std::string const & toString( void ) const = 0;

		virtual ~IOperand( void ) {}
};

# endif