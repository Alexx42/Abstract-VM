/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:00:19 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/29 02:29:50 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECCOMMAND_HPP
# define EXECCOMMAND_HPP

#include <vector>
#include <map>
#include <functional>
#include "Error.hpp"
#include "Operand.hpp"

enum eCommands {
	Add, Sub, Push, Mod,
	Mul, Assert, Print,
	Pop, Div, Dump, Exit
};

class ExecCommand {
	public:
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
		void		mul_s( IOperand const * );
		void		assert_s( IOperand const * );
		void		exit_s( IOperand const * );
		void		dump_s( IOperand const * );
		void		print_s( IOperand const * );

		std::vector<std::pair<std::string, const IOperand *>> 	_exec;
		std::vector< IOperand const * >							_s;
		
		typedef struct 		s_exec {
			eCommands		e;
			std::string		e_val;
			t_command_fn	fn;
		}					t_exec;

		t_exec		execFn[11];
};

# endif