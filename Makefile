# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/08 18:45:24 by myapaten          #+#    #+#              #
#    Updated: 2026/02/08 18:45:26 by myapaten         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rush-02

SRC = src/main.c \
	  src/parser.c \
	  src/dictionary.c \
	  src/dict_parse.c \
	  src/convert.c \
	  src/triad.c \
	  src/utils.c \
	  src/utils2.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
