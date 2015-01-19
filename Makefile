# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlechapt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 18:44:55 by rlechapt          #+#    #+#              #
#    Updated: 2015/01/19 22:10:07 by rlechapt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = \
main.c \
draw.c \
image.c

EXT = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -o $(NAME) $(SRC) -L libft -lft -L/usr/X11/lib -lmlx -lX11 -lXext

clean:
	make clean -C ./libft
	rm -f $(EXT)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all
