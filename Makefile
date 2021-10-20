# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2021/10/21 02:37:58 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = main.c calculations.c colors.c fractal.c
LIBFT = libft/libft.a
INCLUDE = libft/includes
SDL2 = `sdl2-config --cflags` `sdl2-config --libs`
FILES = $(addprefix src/, $(SRC))
.PHONY: clean fclean re all

all:
	# @make -C libft
	gcc -F ./ $(SDL2) $(FILES) $(LIBFT) -I $(INCLUDE) -o ./$(NAME)

clean:
	# @make clean -C libft

fclean: clean
	rm -f $(NAME)
	# @make fclean -C libft

re: fclean
	make all
