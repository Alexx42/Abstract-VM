/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:57:08 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/27 19:27:25 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

#include <iostream>
#include <string>

class Error : std::exception {
	public:
		Error( void );
		virtual ~Error( void ) throw();
		Error(Error const & rhs);
		Error & operator=(Error const & rhs);
		virtual const char	*what( void ) const throw();
		void		setError(std::string err);
	private:
		std::string _error;
};

# endif