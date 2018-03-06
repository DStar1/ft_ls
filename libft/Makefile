NAME = libft.a

SRC = 	ft_putchar.c \
		ft_putstr.c \
		ft_strlen.c \
		ft_strcpy.c \
		ft_putnbr.c \
		ft_strncpy.c \
		ft_atoi.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strdup.c \
		ft_memset.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_memalloc.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_itoa.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_memdel.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_iswhitespace.c \
		ft_strsplit.c \
		ft_lstadd.c \
		ft_lstnew.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_intlen.c \
		ft_cntstrwords.c \
		ft_isnbr.c \
		ft_putarr.c \
		ft_cntarrwords.c \
		round_up_sqrt.c \
		free_array.c \
		ft_strjoin_clr_1st.c \
		get_next_line.c \
		ft_cntdelim.c \
		ft_atoi_base.c \
		ft_power.c \
		ft_hextoi.c \
		ft_abs.c \
		ft_memncpy.c \
		ft_swap.c \
		ft_lstsize.c

PRINTF = 	ft_printf/parse.c \
			ft_printf/string.c \
			ft_printf/ft_int.c \
			ft_printf/ft_puthex.c \
			ft_printf/ft_hex.c \
			ft_printf/ft_pf_intlen.c \
			ft_printf/ft_pf_putnbr.c \
			ft_printf/ft_percent.c \
			ft_printf/ft_unsigned_int.c \
			ft_printf/ft_oct.c \
			ft_printf/ft_putoct.c \
			ft_printf/ft_pointer.c \
			ft_printf/wchars.c \
			ft_printf/ft_print_bits.c \
			ft_printf/flags.c \
			ft_printf/ft_n.c \
			ft_printf/ft_printf.c

all: $(NAME)

$(NAME):
	gcc -c -Wall -Werror -Wextra $(SRC) $(PRINTF)
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
