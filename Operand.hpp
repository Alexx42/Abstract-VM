/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:32:17 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/28 19:54:50 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"

template <typename T>
class Operand : public IOperand {
	public:
		/*
		** Canonical form 
		*/
		Operand( std::string val, int precision, eOperandType type ) 
		: _val(val), _precision(precision), _type(type) {;}
		~Operand( void ) {;}
		Operand(Operand const & rhs) {*this = rhs;}
		Operand & operator=(Operand const & rhs) {static_cast<void>(rhs);return *this;}

		/*
		** Get functions
		*/
		int					getPrecision( void ) const {return _precision;}
		eOperandType		getType( void ) const {return _type;}
		std::string const &	toString( void ) const {return _val;}

		/*
		** Operators
		*/
		IOperand const * operator+(IOperand const & rhs) const {
			static_cast<void>(rhs);
			return this;
		}

		IOperand const * operator-(IOperand const & rhs) const {
			static_cast<void>(rhs);
			return this;	
		}

		IOperand const * operator*(IOperand const & rhs) const {
			static_cast<void>(rhs);
			return this;
		}

		IOperand const * operator/(IOperand const & rhs) const {
			static_cast<void>(rhs);
			return this;	
		}

		IOperand const * operator%(IOperand const & rhs) const {
			static_cast<void>(rhs);
			return this;	
		}

	private:
		std::string		_val;
		int				_precision;
		eOperandType	_type;
};


# endif