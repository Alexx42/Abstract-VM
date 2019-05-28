/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:59:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/27 19:27:43 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

Error::Error( void ) {
	;
}

Error::~Error( void ) throw() {
	;
}

Error::Error(Error const & rhs) {
	*this = rhs;
	return ;
}

Error & Error::operator=(Error const & rhs) {
	this->_error = rhs._error;
	return *this;
}

void		Error::setError( std::string err ) {
	_error = err;
	return ;
}

const char	*Error::what( void ) const throw() {
	return _error.c_str();
}