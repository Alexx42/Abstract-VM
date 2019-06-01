/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:57:08 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/01 00:36:47 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

#include <sstream>
#include <iostream>
#include <string>
#define RED	"\033[31m"	/* Red */

class Error : std::exception {
	public:
		Error( std::string err, std::string type, int ln );
		virtual ~Error( void ) throw();
		Error(Error const & rhs);
		Error & operator=(Error const & rhs);
	protected:
		std::string _error;
		std::string	_type;
		int			_ln;
};

# endif