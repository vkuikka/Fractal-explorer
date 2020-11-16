# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2020/11/16 20:16:19 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
LIBFT = libft/libft.a
FILES = main.c input.c fractal.c colors.c calculations.c start_fractal.c
FDF = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
INCLUDE = libft/includes
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	gcc -o $(NAME) -Wall -Wextra -Werror -O3 $(FILES) $(LIBFT) -I $(INCLUDE) $(FDF) $(ASD)
	@make -C libft

no:
	gcc -o $(NAME) $(FILES) $(LIBFT) -I $(INCLUDE) $(FDF)

clean:
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

re: fclean
	make all
