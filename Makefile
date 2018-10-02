# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/31 11:28:46 by sjuery            #+#    #+#              #
#    Updated: 2018/10/01 18:03:01 by sjuery           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

SRC		= srcs/fdf.c \
		  srcs/draw.c \

OBJ 	= $(SRC:.c=.o)
CFLAG	= -Wall -Wextra -Werror -g
.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	printf '\033[31m[...] %s\n\033[0m' "Creating FdF Player"
	make -C srcs/libft/
	gcc $(CFLAG) -L srcs/minilibx srcs/libft/libft.a -lmlx -framework OpenGL -framework AppKit -I srcs/minilibx $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created FdF Player"

clean:
	printf '\033[31m[...] %s\n\033[0m' "Cleaning FdF Player"
	make fclean -C srcs/libft/
	/bin/rm -f srcs/*.o
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Cleaned FdF Player"

fclean: clean
	make fclean -C srcs/libft/
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all test
