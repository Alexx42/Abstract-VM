/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:06:13 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/27 22:51:24 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

int			main(int ac, char **av)
{
	Parser parser;
	if (ac == 2)
		parser = Parser(av[1]);
	else
		parser = Parser("");
	return (0);	
}