/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:06:13 by ale-goff          #+#    #+#             */
/*   Updated: 2019/05/29 02:35:36 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "ExecCommand.hpp"

int			main(int ac, char **av)
{
	Parser parser;
	if (ac == 2)
		parser = Parser(av[1]);
	else
		parser = Parser("");
	parser.read_content();
	// parser.printParse();
	if (parser.printError()) {
		return (1);
	}
	ExecCommand e = ExecCommand(parser.getParse());
	e.execCommands();
	return (0);
}