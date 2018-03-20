/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:53:44 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 18:09:28 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		oct_data(t_print *print, t_flags *f)
{
	print->data.super_u = va_arg(print->ap, uintmax_t);
	if (f->res == 'O')
		print->data.super_u = (unsigned long)print->data.super_u;
	else if (f->h)
		print->data.super_u = (unsigned short)print->data.super_u;
	else if (f->hh)
		print->data.super_u = (unsigned char)print->data.super_u;
	else if (f->l)
		print->data.super_u = (unsigned long)print->data.super_u;
	else if (f->ll)
		print->data.super_u = (unsigned long long)print->data.super_u;
	else if (f->j)
		print->data.super_u = (uintmax_t)print->data.super_u;
	else if (f->z)
		print->data.super_u = (size_t)print->data.super_u;
	else if (f->res == 'o')
		print->data.super_u = (unsigned int)print->data.super_u;
}

static void	neg_zero(t_print *print, t_flags *f, int cap)
{
	if (f->p2)
	{
		if (f->p2 > f->intlen)
			fill_space('0', f->p2 - f->intlen);
		ft_putoct(print->data.super_u, print, cap);
		(f->intlen < f->width) ? fill_space(' ', f->width - f->p2) : 0;
	}
	else
	{
		if (f->hash && print->data.super_u != 0)
		{
			ft_putchar('0');
			f->intlen++;
		}
		if (f->zero)
			fill(f, print, '0');
		ft_putoct(print->data.super_u, print, cap);
		if (!f->zero)
			fill(f, print, ' ');
	}
}

static void	not_neg_zero(t_print *print, t_flags *f, int cap)
{
	if (f->p2)
	{
		(f->intlen < f->width) ? fill_space(' ', f->width - f->p2) : 0;
		if (f->p2 > f->intlen)
			fill_space('0', f->p2 - f->intlen);
		ft_putoct(print->data.super_u, print, cap);
	}
	else
	{
		(f->hash && print->data.super_u != 0) ? f->intlen++ : 0;
		fill(f, print, ' ');
		if (f->hash && print->data.super_u != 0)
			ft_putchar('0');
		ft_putoct(print->data.super_u, print, cap);
	}
}

void		ft_oct(t_print *print, t_flags *f, int cap)
{
	f->intlen = 0;
	oct_data(print, f);
	if ((check_zero(print, f, print->data.super_u) != 0)
							|| (f->p && !f->p2 && !f->hash))
		return ;
	ft_octlen(print->data.super_u, f);
	(f->p2 > f->width) ? f->width = f->p2 : 0;
	(f->intlen > f->width) ? f->width = f->intlen : 0;
	(f->intlen > f->p2) ? f->p2 = 0 : 0;
	f->tmp = f->width;
	IF(f->neg, f->zero = 0);
	if (f->neg || f->zero)
		neg_zero(print, f, cap);
	else
		not_neg_zero(print, f, cap);
	f->width = f->tmp;
	IF(f->width < f->intlen, f->width = f->intlen);
	IFELSE((f->width == 0), print->ret += f->intlen, print->ret += f->width);
}
