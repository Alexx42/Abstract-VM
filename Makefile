# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 21:33:09 by ale-goff          #+#    #+#              #
#    Updated: 2019/05/27 22:08:19 by ale-goff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = avm

SRCS = avm.cpp Error.cpp Parser.cpp
OBJ =  avm.o Error.o Parser.o

CXX = clang++
CXXFLAGS = -g -fsanitize=address -Wall -Werror -Wextra -std=c++11

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