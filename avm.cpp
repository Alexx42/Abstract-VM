/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:06:13 by ale-goff          #+#    #+#             */
/*   Updated: 2019/06/02 22:14:45 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "ExecCommand.hpp"
#include "Flags.hpp"

int			main(int ac, char **av)
{
	Parser parser;
	Flags flag(av);
	flag.parserStr();
	parser = Parser(flag.getNbFlags() == ac - 1 ? "" : av[ac - 1]);
	
	parser.read_content();
	if (flag.getDebug()) {
		parser.printParse();
		std::cout << std::endl;
	}
	if (parser.printError()) {
		return (1);
	}
	ExecCommand e = ExecCommand(parser.getParse());
	e.execCommands();
	return (0);
}