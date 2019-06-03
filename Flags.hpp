/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flags.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 20:45:01 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/02 21:24:47 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_HPP
# define FLAGS_HPP

#include <iostream>
#include <string>

class Flags {
	public:
		Flags( char **str );
		~Flags( void );
		Flags( Flags const & rhs );
		Flags & operator=(Flags const & rhs);

		void		parserStr( void );
		int			getNbFlags( void );
		int			getDebug( void );
	private:
		char		**_str;
		int			_h;
		int			_d;
		int			_nbFlags;
		void		printHelp( void );
};


# endif