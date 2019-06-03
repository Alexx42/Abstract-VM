/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:57:08 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/02 15:48:21 by ale-goff         ###   ########.fr       */
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
		Error( const std::string & err );
		virtual ~Error( void ) throw();
		Error(Error const & rhs);
		Error & operator=(Error const & rhs);
		virtual const char	*what() const throw();
	protected:
		std::string _error;
};

# endif