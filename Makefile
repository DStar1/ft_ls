# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 15:20:50 by hasmith           #+#    #+#              #
#    Updated: 2018/03/18 21:05:54 by hasmith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIB = lib.a

LIBFT = libft/libft.a

GIT = test

MAIN = main.c

TEST = <argv[1]>

# OBJ = $(addprefix ./objects/, $(SRC:.c=.o))

# IFLAG	= -I libft -I includes -g

SRC = 	srcs/ft_ls.c srcs/ft_subdir.c srcs/dash_l.c

FLAGS = -Wall -Werror -Wextra -g

.SILENT:#doesn't show the behind the scenes stuff

all: $(NAME)

$(NAME):
	make all -C libft
	gcc -g -c $(SRC)
	cp $(LIBFT) $(LIB)
	ar rcs $(LIB) *.o
	gcc $(FALGS) -g -o $(NAME) $(SRC) $(LIBFT)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created $(NAME)"

# $(NAME): $(OBJ)
# 	make -C libft/
# 	gcc $(FALGS) -L libft -lft -I includes $^ -o $(NAME)

# ./objects/%.o: ./srcs/%.c
# 	mkdir -p objects
# 	gcc $(IFLAG) -c $< -o $@

cmain:
	make re
	./ft_ls
	make clean

clean:
	/bin/rm -f *.o
	make clean -C libft
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned $(NAME)"

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME) $(LIB)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned $(NAME)"

re: fclean all

git:
	make fclean
	git add *
	git commit -m '$(GIT)'
	git push
