/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:56:20 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/27 23:02:58 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>
#include <string>
#include "IOperand.hpp"
#include "Error.hpp"

class Parser {
	public:
		Parser( void );
		Parser( std::string str );
		~Parser( void );
		Parser( Parser const & rhs );
		Parser & operator=( Parser const & rhs );
	private:
		void		choose_read();
		void		read_stdin();
		void		read_file();
		bool		verify_instruction( std::string instr );
		bool		verify_type( std::string type );
		bool		verify_value( std::string val );
		std::string _str;
		std::vector <IOperand*> lines;
		
};

# endif