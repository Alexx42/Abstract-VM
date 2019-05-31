/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:32:17 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/30 23:44:30 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"
#include "CreateOperand.hpp"
#include "Error.hpp"

class CreateOperand;
template <typename T>
class Operand : public IOperand {
	public:
		Operand( std::string val, int precision, eOperandType type, const CreateOperand *c) 
		: _val(val), _precision(precision), _type(type), cr(c) {;}
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
			
			Error			err;
			eOperandType	e = getType() > rhs.getType() ? getType() : rhs.getType();
			int				precision = getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision();
			static_cast<void>(precision);
			if (e < FLOAT) {
				try {
					long long		val = std::stoll(this->toString()) + std::stoll(this->toString());
					if (hasOUflow<long long>(val, e)) {
						err.setError("Overflow | Underflow");
						throw err;
						return (cr->createOperand(e, std::to_string(val)));
					}
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			} else {
				
			}
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
		template <typename U>
		bool		hasOUflow(U value, eOperandType e) const {
			switch (e) {
				case (INT8) :
					return ((value > INT8_MAX || (value < INT8_MIN)));
				case (INT16) :
					return ((value > INT8_MAX || (value < INT8_MIN)));
				case (INT32) :
					return ((value > INT8_MAX || (value < INT8_MIN)));
				case (FLOAT) :
					return (false);
				case (DOUBLE) :
					return (false);
			}
			return (false);
		}
	private:
		std::string		_val;
		int				_precision;
		eOperandType	_type;
		const CreateOperand		*cr;
	};

# endif