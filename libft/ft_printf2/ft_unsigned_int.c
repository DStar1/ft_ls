/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 22:00:52 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 18:42:26 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		u_data(t_print *p, t_flags *f)
{
	p->data.super_u = va_arg(p->ap, uintmax_t);
	if (f->res == 'U')
		p->data.super_u = (unsigned long)p->data.super_u;
	else if (f->h)
		p->data.super_u = (unsigned short)p->data.super_u;
	else if (f->hh)
		p->data.super_u = (unsigned char)p->data.super_u;
	else if (f->l)
		p->data.super_u = (unsigned long)p->data.super_u;
	else if (f->ll)
		p->data.super_u = (unsigned long long)p->data.super_u;
	else if (f->j)
		p->data.super_u = (uintmax_t)p->data.super_u;
	else if (f->z)
		p->data.super_u = (size_t)p->data.super_u;
	else if (f->res == 'u')
		p->data.super_u = (unsigned int)p->data.super_u;
}

static void	width(t_print *p, t_flags *f)
{
	if (f->neg)
	{
		if (f->p2)
		{
			if (f->p2 > f->intlen)
				fill_space('0', f->p2 - f->intlen);
			ft_pf_putnbr(p->data.super_u);
			(f->intlen < f->width) ? fill_space(' ', f->width - f->p2) : 0;
		}
		else
			BRACKETS(ft_pf_putnbr(p->data.super_u), fill(f, p, ' '));
	}
	else
	{
		if (f->p2)
		{
			(f->intlen < f->width) ? fill_space(' ', f->width - f->p2) : 0;
			if (f->p2 > f->intlen)
				fill_space('0', f->p2 - f->intlen);
			ft_pf_putnbr(p->data.super_u);
		}
		else
			BRACKETS(fill(f, p, ' '), ft_pf_putnbr(p->data.super_u));
	}
}

void		ft_unsigned_int(t_print *p, t_flags *f)
{
	u_data(p, f);
	if (check_zero(p, f, p->data.super_u) != 0)
		return ;
	f->intlen = ft_pf_intlen(p->data.super_u);
	(f->p2 <= f->intlen) ? f->p2 = 0 : 0;
	if (f->width || f->p2 > f->width)
	{
		width(p, f);
		IF(f->intlen > f->width, f->width = f->intlen);
		IF(f->p2 > f->width, f->width = f->p2);
		p->ret += f->width;
	}
	else
	{
		ft_pf_putnbr(p->data.super_u);
		p->ret += f->intlen;
	}
}
