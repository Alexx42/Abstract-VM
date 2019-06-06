/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateOperand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:52:39 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/06 12:16:53 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_OPERAND_HPP
# define CREATE_OPERAND_HPP

#include <functional>
#include <map>
#include "IOperand.hpp"
#include "Parser.hpp"

class CreateOperand {
	public:
		CreateOperand( void );
		~CreateOperand( void );
		CreateOperand( CreateOperand const & rhs );
		CreateOperand & operator=(CreateOperand const & rhs);

		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	private:
		IOperand const *createInt8( std::string const & value ) const;
		IOperand const *createInt16( std::string const & value ) const;
		IOperand const *createInt32( std::string const & value ) const;
		IOperand const *createFloat( std::string const & value ) const;
		IOperand const *createDouble( std::string const & value ) const;

		std::map< eOperandType , std::function<IOperand const *( std::string const & value)> > disp;
};

# endif