# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtolochk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/20 15:02:45 by vtolochk          #+#    #+#              #
#    Updated: 2018/05/03 20:31:56 by vtolochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

NAME = ft_select

HEADER = includes/ft_select.h

SRCS = srcs/ft_select.c srcs/mods.c srcs/list_funcs.c srcs/print_files.c srcs/signals.c srcs/print_one_file.c \
srcs/getters.c srcs/moves.c srcs/helpers.c srcs/select_all.c

OBJ = $(SRCS:.c=.o)

LIBFT = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -Iincludes

CC = gcc

all: lib $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) libft/libft.a
	gcc $(CFLAGS) -ltermcap $(LIBFT) $(OBJ) -o $(NAME)

lib:
	make -C ./libft/

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
