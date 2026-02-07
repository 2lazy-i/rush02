# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/07 14:29:45 by 2lazy             #+#    #+#              #
#    Updated: 2026/02/07 14:55:20 by 2lazy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rush02
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/parser.c src/dictionary.c src/convert.c src/triad.c src/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all