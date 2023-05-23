# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 19:24:43 by caalbert          #+#    #+#              #
#    Updated: 2023/02/07 03:59:36 by caalbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror

all: client server

client: client.c libft/libft.a
	$(CC) $(CFLAGS) -I./inc client.c -L./libft -lft -o client

server: server.c libft/libft.a
	$(CC) $(CFLAGS) -I./inc server.c -L./libft -lft -o server

libft/libft.a:
	make -C libft

clean:
	rm -f client server *.o

fclean: clean
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re