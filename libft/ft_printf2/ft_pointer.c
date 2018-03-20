/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:42:30 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 18:21:02 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		p_data(t_print *print, t_flags *flags)
{
	print->data.super_u = va_arg(print->ap, uintmax_t);
	if (flags->h)
		print->data.super_u = (unsigned int)print->data.super_u;
	else if (flags->hh)
		print->data.super_u = (unsigned int)print->data.super_u;
	else if (flags->l)
		print->data.super_u = (unsigned long)print->data.super_u;
	else if (flags->ll)
		print->data.super_u = (unsigned long long)print->data.super_u;
	else if (flags->j)
		print->data.super_u = (uintmax_t)print->data.super_u;
	else if (flags->z)
		print->data.super_u = (size_t)print->data.super_u;
	else
		print->data.super_u = (uintmax_t)print->data.super_u;
}

static void	width(t_flags *flags, t_print *print)
{
	if (flags->neg)
	{
		ft_putstr("0x");
		if (flags->p2 || flags->zero)
			fill_space('0', flags->p2 + 2 - flags->intlen);
		ft_puthex(print->data.super_u, print, 0);
		IF(flags->width != flags->p2 + 2, fill(flags, print, ' '));
	}
	else
	{
		if (!(flags->zero && flags->intlen < flags->width))
			fill_space(' ', flags->width - flags->intlen);
		ft_putstr("0x");
		if (flags->p2)
			fill_space('0', flags->p2 + 2 - flags->intlen);
		else if (flags->zero)
			fill_space('0', flags->width - flags->intlen);
		ft_puthex(print->data.super_u, print, 0);
	}
	print->ret += flags->width;
}

static void	no_width(t_flags *flags, t_print *print)
{
	ft_putstr("0x");
	ft_puthex(print->data.super_u, print, 0);
	print->ret += flags->intlen;
}

void		ft_pointer(t_flags *flags, t_print *print)
{
	p_data(print, flags);
	ft_hexlen(print->data.super_u, flags);
	flags->intlen += 2;
	if (check_zero(print, flags, print->data.super_u) != 0)
	{
		ft_putstr("0x");
		print->ret += 2;
		return ;
	}
	(flags->intlen > flags->width) ? flags->width = flags->intlen : 0;
	(flags->intlen > flags->p2) ? flags->p2 = 0 : 0;
	(flags->p2) ? flags->zero = 0 : 0;
	if (flags->p2 + 2 > flags->width)
	{
		flags->width = flags->p2 + 2;
		flags->zero++;
		flags->neg++;
	}
	(flags->width < flags->intlen) ? flags->width = 0 : 0;
	if (flags->width)
		width(flags, print);
	else
		no_width(flags, print);
}
