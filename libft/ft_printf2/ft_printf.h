/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/05 21:05:47 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>

# define HEX "0123456789abcdef0123456789ABCDEF"
# define OCT "0123456701234567"

/*
** define colors:
** ft_printf(RED"\nhello"EOC" to all\n");
*/

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define EOC     "\x1b[0m"

typedef union
{
	char			c;
	wchar_t			wc;
	char			*str;
	wchar_t			*wstr;
	int				i;
	intmax_t		super;
	uintmax_t		super_u;
	void			*ptr;
}					t_uni;

typedef struct		s_print
{
	int				ret;
	int				i;
	int				fd;
	char			*fmt;
	va_list			ap;
	t_uni			data;
}					t_print;

typedef struct		s_flags
{
	int				hash;
	int				zero;
	int				space;
	int				neg;
	int				pos;
	int				perc;
	int				width;
	int				len;
	int				intlen;
	int				l;
	int				ll;
	int				h;
	int				hh;
	int				j;
	int				z;
	int				p;
	int				p1;
	int				p2;
	int				tmp;
	int				ncheck;
	char			res;
	int				i;
}					t_flags;

typedef struct		s_master
{
	int				i;
	int				j;
	void			*somthing;
	struct s_master	*next;
}					t_master;

int					ft_printf(char *fmt, ...);
void				parse(t_print *ptf, t_flags *flags);
void				ft_string(t_print *print, t_flags *flags);
void				ft_char(t_print *print, t_flags *flags);
void				ft_int(t_print *print, t_flags *flags);
void				ft_unsigned_int(t_print *print, t_flags *flags);
void				ft_l_char(t_print *print, t_flags *flags);
void				ft_octal(t_print *print, t_flags *flags);
void				fill(t_flags *flags, t_print *ptf, char c);
void				ft_int(t_print *print, t_flags *flags);
void				ft_puthex(uintmax_t nb, t_print *print, int cap);
void				ft_hex(t_print *print, t_flags *flags, int cap);
void				ft_hexlen(uintmax_t nb, t_flags *flags);
void				ft_pf_putnbr(uintmax_t n);
int					ft_pf_intlen(uintmax_t n);
void				ft_percent(t_print *print, t_flags *flags);
void				ft_unsigned_int(t_print *print, t_flags *flags);
void				ft_oct(t_print *print, t_flags *flags, int cap);
void				ft_putoct(uintmax_t nb, t_print *print, int cap);
void				fill_space(char c, int len);
int					check_zero(t_print *print, t_flags *flags, uintmax_t res);
void				ft_octlen(uintmax_t nb, t_flags *flags);
void				ft_pointer(t_flags *flags, t_print *print);
int					wchar_convert(int c);
void				ft_wchar_string(t_print *print, t_flags *flags);
void				ft_wchar(t_print *print, t_flags *flags);
void				print_bits(unsigned char octet);
void				set_flags(t_flags *flags);
int					pf_atoi(t_print *p);
int					res_flags(char c);
void				ft_n(t_print *print);

#endif
