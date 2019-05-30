/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:56:20 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/29 22:23:37 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <map>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include "IOperand.hpp"
#include "CreateOperand.hpp"
#include "Error.hpp"
#include <fstream>

struct	Infos {
	std::string type;
	double		min;
	double		max;
};

class Parser {
	public:
		Parser( void );
		Parser( std::string str );
		~Parser( void );
		Parser( Parser const & rhs );
		Parser & operator=( Parser const & rhs );
		void				read_content();
		void				printParse();
		bool				printError( void );
		std::vector<std::pair<std::string, const IOperand *>> & getParse();
	private:
		std::vector<std::pair<std::string, bool>>::iterator verify_instruction( std::string );
		IOperand const		*verify_type( std::vector<std::pair<std::string, bool>>::iterator , std::string );
		std::string			verify_value( std::string, eOperandType );
		void				initVector();
		eOperandType		getEnumValue( std::string );

		std::string 											_str;
		std::vector<std::pair<std::string, bool>>				_v;
		std::vector <Infos>										_type;
		std::vector <std::pair<std::string, const IOperand *>>	_parse;
		std::queue<Error>										_queueErr;

		static std::string										extractString( std::string , char , char );
		static int												count_words( std::string );
		static void												isNumber( std::string val );
		static void												removeZero( std::string & val );
};

# endif