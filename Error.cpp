/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:59:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/01 00:31:03 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

Error::Error( std::string err, std::string type, int ln )  : _error(err), _type(type), _ln(ln) {
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

