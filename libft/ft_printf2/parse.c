/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 19:05:59 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 19:50:45 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		apply_functs(t_print *p, t_flags *flags)
{
	if ((flags->res == 's' && flags->l) || (flags->res == 'S' && flags->l))
		ft_wchar_string(p, flags);
	else if ((flags->res == 's') || (flags->res == 'S'))
		ft_string(p, flags);
	if (flags->res == 'c' && flags->l)
		ft_wchar(p, flags);
	else if (flags->res == 'c')
		ft_char(p, flags);
	(flags->res == 'C') ? ft_char(p, flags) : 0;
	((flags->res == 'd') || (flags->res == 'i')
					|| (flags->res == 'D')) ? ft_int(p, flags) : 0;
	(flags->res == 'o' || flags->res == 'O') ? ft_oct(p, flags, 0) : 0;
	(flags->res == 'u' || flags->res == 'U') ? ft_unsigned_int(p, flags) : 0;
	(flags->res == 'x') ? ft_hex(p, flags, 0) : 0;
	(flags->res == 'X') ? ft_hex(p, flags, 1) : 0;
	(flags->res == '%') ? ft_percent(p, flags) : 0;
	(flags->res == 'p') ? ft_pointer(flags, p) : 0;
	(flags->res == 'n') ? ft_n(p) : 0;
	if (flags->res == 'b')
	{
		p->data.super_u = (unsigned char)va_arg(p->ap, uintmax_t);
		print_bits(p->data.super_u);
		p->ret += 8;
	}
}

int				check_flags(t_print *p)
{
	if (p->fmt[p->i] == '#' || p->fmt[p->i] == '+' ||
		p->fmt[p->i] == '-' || p->fmt[p->i] == '0' ||
		p->fmt[p->i] == ' ')
		return (1);
	if (p->fmt[p->i] == 'l' || p->fmt[p->i] == 'h' ||
		p->fmt[p->i] == 'j' || p->fmt[p->i] == 'z')
		return (1);
	return (0);
}

static void		loop(t_print *p, t_flags *flags, int j, int mod)
{
	while (p->fmt[p->i] && (check_flags(p)))
	{
		IF(p->fmt[p->i] == '#', flags->hash = j++);
		IF(p->fmt[p->i] == '+', flags->pos = j++);
		IF(p->fmt[p->i] == '-', flags->neg = j++);
		IF(p->fmt[p->i] == '0', flags->zero = j++);
		IF(p->fmt[p->i] == ' ', flags->space = j++);
		if (p->fmt[p->i] == 'l' && mod == 1)
			flags->l = mod++;
		else if (p->fmt[p->i] == 'l' && mod == 2)
		{
			flags->l = 0;
			flags->ll = 1;
		}
		if (p->fmt[p->i] == 'h' && mod == 1)
			flags->h = mod++;
		else if (p->fmt[p->i] == 'h' && mod == 2)
		{
			flags->h = 0;
			flags->hh = 1;
		}
		IF(p->fmt[p->i] == 'j', flags->j = mod++);
		IF(p->fmt[p->i] == 'z', flags->z = mod++);
		p->i++;
	}
}

static void		parse2(t_print *p, t_flags *flags)
{
	if (p->fmt[p->i] && res_flags(p->fmt[p->i]))
	{
		flags->res = p->fmt[p->i];
		if (p->fmt[p->i])
			apply_functs(p, flags);
	}
	else if (p->fmt[p->i - 1])
	{
		p->i--;
		if (flags->width)
		{
			p->ret += flags->width - 1;
			if (!flags->zero)
				fill_space(' ', flags->width - 1);
			else if (flags->zero)
				fill_space('0', flags->width - 1);
		}
	}
}

void			parse(t_print *p, t_flags *flags)
{
	int		j;
	int		mod;

	j = 1;
	mod = 1;
	set_flags(flags);
	p->i++;
	loop(p, flags, j, mod);
	if ((p->fmt[p->i]))
	{
		if (p->fmt[p->i] && ft_isdigit(p->fmt[p->i]))
			flags->width = pf_atoi(p);
		if (p->fmt[p->i] && p->fmt[p->i + 1] &&
						ft_isdigit(p->fmt[p->i + 1]) && p->fmt[p->i] == '.')
		{
			p->i++;
			flags->p = 1;
			flags->p2 = pf_atoi(p);
		}
		IF(p->fmt[p->i] && p->fmt[p->i] == '.', (flags->p = 1 && p->i++));
	}
	parse2(p, flags);
	return ;
}
