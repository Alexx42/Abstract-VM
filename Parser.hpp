/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:56:20 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/02 20:11:10 by ale-goff         ###   ########.fr       */
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
	eOperandType	e;
	std::string		type;
	double			min;
	double			max;
};

class Parser {
	public:
		class ParserError : public Error {
			public:
				ParserError( const std::string & err );
				virtual ~ParserError( void ) throw();
				ParserError( ParserError const & rhs );
				ParserError & operator=( ParserError const & rhs );
		};
		Parser( void );
		Parser( std::string str );
		~Parser( void );
		Parser( Parser const & rhs );
		Parser & operator=( Parser const & rhs );
		void				read_content();
		void				printParse();
		bool				printError( void );
		static void			removeZero( std::string & val );
		std::vector<std::pair<std::string, const IOperand *>> & getParse();
	private:
		std::vector<std::pair<std::string, bool>>::iterator verify_instruction( std::string );
		IOperand const		*verify_type( std::vector<std::pair<std::string, bool>>::iterator , std::string );
		std::string			verify_value( std::string, eOperandType );
		void				initVector();

		std::string 											_str;
		std::vector<std::pair<std::string, bool>>				_v;
		std::vector <Infos>										_type;
		std::vector <std::pair<std::string, const IOperand *>>	_parse;
		std::queue<ParserError>									_queueErr;

		static std::string										extractString( std::string , char , char );
		static int												count_words( std::string );
		static void												isNumber( std::string val );
		static int												_ln;
		
};

# endif