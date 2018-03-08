# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 15:20:50 by hasmith           #+#    #+#              #
#    Updated: 2018/03/08 01:31:40 by hasmith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIB = lib.a

LIBFT = libft/libft.a

GIT = test

MAIN = main.c

TEST = <argv[1]>

SRC = 	srcs/ft_ls.c srcs/ft_subdir.c

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make all -C libft
	gcc -g -c $(SRC)
	cp $(LIBFT) $(LIB)
	ar rcs $(LIB) *.o
	gcc $(FALGS) -g -o $(NAME) $(SRC) $(LIBFT)

cmain:
	make re
	./ft_ls
	make clean

clean:
	/bin/rm -f *.o
	make clean -C libft

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME) $(LIB)

re: fclean all

git:
	make fclean
	git add *
	git commit -m '$(GIT)'
	git push
