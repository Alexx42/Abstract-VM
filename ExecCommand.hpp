/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:00:19 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/02 20:40:27 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_COMMAND_HPP
# define EXEC_COMMAND_HPP

#include <vector>
#include <map>
#include <functional>
#include "Error.hpp"
#include "IOperand.hpp"

enum eCommands {
	Add, Sub, Push, Mod,
	Mul, Assert, Print,
	Max, Min, Pop, Div,
	Dump, Exit
};

class ExecCommand {
	public:
		class ExecError : public Error {
			public:
				ExecError( const std::string & err );
				virtual ~ExecError( void ) ;
				ExecError( ExecError const & rhs );
				ExecError & operator=( ExecError const & rhs );
		};
		ExecCommand( std::vector<std::pair<std::string, const IOperand*>>);
		~ExecCommand( void );
		ExecCommand( ExecCommand const & rhs);
		ExecCommand & operator=(ExecCommand const & rhs);

		void		execCommands( void );
		
	private:
		typedef void (ExecCommand::*t_command_fn)( IOperand const * );
		void		push_s( IOperand const * );
		void		pop_s( IOperand const * );
		void		add_s( IOperand const * );
		void		sub_s( IOperand const * );
		void		mod_s( IOperand const * );
		void		div_s( IOperand const * );
		void		max_s( IOperand const * );
		void		min_s( IOperand const * );
		void		mul_s( IOperand const * );
		void		assert_s( IOperand const * );
		void		exit_s( IOperand const * );
		void		dump_s( IOperand const * );
		void		print_s( IOperand const * );

		std::vector<std::pair<std::string, const IOperand *>> 	_exec;
		std::vector< const IOperand  * >						_s;
		
		typedef struct 		s_exec {
			eCommands		e;
			std::string		e_val;
			t_command_fn	fn;
		}					t_exec;
		static int												_ln;
		t_exec													execFn[13];
};

# endif