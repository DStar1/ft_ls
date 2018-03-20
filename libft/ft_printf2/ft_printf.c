/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:24:34 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 18:23:52 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** man 3 printf
** http://en.cppreference.com/w/cpp/io/c/fprintf
** Modifiers
** hh: signed char
** h: short
** l: long
** ll: long long
** j: intmax_t(d, i)   uintmax_t(o, u, x, X)
** z: signed size_t
** Identifiers
** s: print str ft_putstr()
** S: s with l modifier
** p: print hex
** d: digit (use va_arg(read, convert/cast)) ex: va_arg(d, long long)
** D: same as d?
** i: same as d?
** o: octal integer
** O: l modifier with o
** u: unsigned int
** U: l modifier with u
** x: hex integer lower case
** X: hex capital
** c: int converted to unsigned char, char is written
** C: c with 1 modifier wchar
** %%: no args?
** FLAGS
** #:
** 0: field padded with 0's
** -: left justify
** +: right justify
** ' ': positive values begin with blank
** Minimum field width:
** precision:
*/

void	fill(t_flags *flags, t_print *ptf, char c)
{
	int i;

	i = 0;
	(void)ptf;
	if (!flags->neg && flags->zero > flags->neg)
		c = '0';
	while (i < flags->width - flags->intlen)
	{
		write(1, &c, 1);
		flags->len++;
		i++;
	}
	return ;
}

void	fill_space(char c, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		i++;
	}
}

int		check_zero(t_print *print, t_flags *flags, uintmax_t res)
{
	if (res == 0)
	{
		if (flags->p && flags->p2 == 0)
		{
			if (flags->res == 'O' || (flags->res == 'o' && flags->hash))
				return (0);
			if (flags->width && flags->res == 'p')
				fill_space(' ', flags->width - 2);
			else if (flags->width)
				fill_space(' ', flags->width);
			print->ret += flags->width;
			return (1);
		}
	}
	return (0);
}

int		ft_printf(char *fmt, ...)
{
	t_print ptf;
	t_flags	flags;

	ptf.ret = 0;
	ptf.fd = 1;
	ptf.fmt = (char*)fmt;
	va_start(ptf.ap, fmt);
	ptf.i = 0;
	while (ptf.fmt[ptf.i])
	{
		if (ptf.fmt[ptf.i] != '%')
		{
			ft_putchar((ptf.fmt[ptf.i]));
			ptf.ret++;
		}
		else
		{
			parse(&ptf, &flags);
		}
		if (!ptf.fmt[ptf.i])
			break ;
		ptf.i++;
	}
	va_end(ptf.ap);
	return (ptf.ret);
}
