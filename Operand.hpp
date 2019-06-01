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
# define DBL_MIN std::numeric_limits<float>::lowest()
# define DBL_MAX -DBL_MIN
# define FLT_MIN std::numeric_limits<float>::lowest()
# define FLT_MAX -FLT_MIN
#include "IOperand.hpp"
#include "CreateOperand.hpp"
#include "Error.hpp"

// class CreateOperand;
template <typename T>
class Operand : public IOperand {
	public:
		Operand( std::string val, int precision, eOperandType type) 
		: _val(val), _precision(precision), _type(type){_cr = new CreateOperand;}
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
					}
					const IOperand *res = _cr->createOperand(e, std::to_string(val));
					return (res);
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			} else {
				try {
					long double		val = std::stold(this->toString()) % std::stold(this->toString());
					if (hasOUflow<long double>(val, e)) {
						err.setError("Overflow | Underflow");
						throw err;
					}
					return (_cr->createOperand(e, std::to_string(val)));
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			}
			return this;
		}

		IOperand const * operator-(IOperand const & rhs) const {
			Error			err;
			eOperandType	e = getType() > rhs.getType() ? getType() : rhs.getType();
			int				precision = getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision();
			static_cast<void>(precision);
			if (e < FLOAT) {
				try {
					long long		val = std::stoll(this->toString()) - std::stoll(this->toString());
					if (hasOUflow<long long>(val, e)) {
						err.setError("Overflow | Underflow");
						throw err;
					}
					const IOperand *res = _cr->createOperand(e, std::to_string(val));
					return (res);
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			} else {
				
			}
			return this;
		}

		IOperand const * operator*(IOperand const & rhs) const {
			Error			err;
			eOperandType	e = getType() > rhs.getType() ? getType() : rhs.getType();
			int				precision = getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision();
			static_cast<void>(precision);
			if (e < FLOAT) {
				try {
					long long		val = std::stoll(this->toString()) * std::stoll(this->toString());
					if (hasOUflow<long long>(val, e)) {
						err.setError("Overflow | Underflow");
						throw err;
					}
					const IOperand *res = _cr->createOperand(e, std::to_string(val));
					return (res);
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			} else {
				
			}
			return this;
		}

		IOperand const * operator/(IOperand const & rhs) const {
			Error			err;
			eOperandType	e = getType() > rhs.getType() ? getType() : rhs.getType();
			int				precision = getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision();
			static_cast<void>(precision);
			if (e < FLOAT) {
				try {
					long long		val = std::stoll(this->toString()) / std::stoll(this->toString());
					if (hasOUflow<long long>(val, e)) {
						err.setError("Overflow | Underflow");
						throw err;
					}
					const IOperand *res = _cr->createOperand(e, std::to_string(val));
					return (res);
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			} else {
				
			}
			return this;	
		}

		IOperand const * operator%(IOperand const & rhs) const {
			Error			err;
			eOperandType	e = getType() > rhs.getType() ? getType() : rhs.getType();
			int				precision = getPrecision() > rhs.getPrecision() ? getPrecision() : rhs.getPrecision();
			static_cast<void>(precision);
			if (e < FLOAT) {
				try {
					long long		val = std::stoll(this->toString()) % std::stoll(this->toString());
					if (hasOUflow<long long>(val, e)) {
						err.setError("Overflow | Underflow");
						throw err;
					}
					return (_cr->createOperand(e, std::to_string(val)));
				} catch (Error e) {
					std::cout << e.what() << std::endl;
				}
			} else {
				double a = 		
			}
			return this;	
		}
		template <typename U>
		bool		hasOUflow(U value, eOperandType e) const {
			switch (e) {
				case (INT8) :
					return ((value > INT8_MAX || (value < INT8_MIN)));
				case (INT16) :
					return ((value > INT16_MAX || (value < INT16_MIN)));
				case (INT32) :
					return ((value > INT32_MAX || (value < INT32_MIN)));
				case (FLOAT) :
					return ((value > FLT_MAX || value < FLT_MIN));
				case (DOUBLE) :
					return (value > DBL_MAX || value < DBL_MIN);
			}
			return (false);
		}
	private:
		std::string				_val;
		int						_precision;
		eOperandType			_type;
		const CreateOperand		*_cr;
	};

# endif