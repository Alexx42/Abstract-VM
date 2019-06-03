# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 21:33:09 by ale-goff          #+#    #+#              #
#    Updated: 2019/06/02 20:57:18 by ale-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = avm

SRCS = avm.cpp Error.cpp Parser.cpp CreateOperand.cpp ExecCommand.cpp Flags.cpp
OBJ =  avm.o Error.o Parser.o CreateOperand.o ExecCommand.o Flags.o

CXX = clang++
CXXFLAGS = -g3 -Wall -Werror -Wextra -std=c++11

all: $(NAME)

%.o:%.cpp
	$(CXX) $(CXXFLAGS)   -o $@   -c $< 

$(NAME): $(OBJ)
	$(CXX)  $(CXXFLAGS) -o $(NAME)  $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all