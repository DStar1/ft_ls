/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:00:03 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 18:00:18 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	int_data(t_print *p, t_flags *f)
{
	p->data.super = va_arg(p->ap, intmax_t);
	if (f->res == 'D')
		p->data.super_u = (unsigned long)p->data.super_u;
	else if (f->h)
		p->data.super = (short int)p->data.super;
	else if (f->hh)
		p->data.super = (char)p->data.super;
	else if (f->l)
		p->data.super = (long int)p->data.super;
	else if (f->ll)
		p->data.super = (long long int)p->data.super;
	else if (f->j)
		p->data.super = (intmax_t)p->data.super;
	else if (f->z)
		p->data.super = (size_t)p->data.super;
	else if (f->res != 'D')
		p->data.super = (int)p->data.super;
}

void	i2(t_print *p, t_flags *f)
{
	if (f->ncheck == -1 && !f->zero)
		ft_putchar('-');
	else if (f->pos && !f->zero)
		BRACKETS(ft_putchar('+'), f->len++);
	((f->p2 > f->width && f->ncheck == -1)) ? (f->intlen--) : 0;
	(f->p2) ? fill_space('0', f->p2 - f->intlen) : 0;
	(p->data.super < 0) ? f->intlen-- : 0;
	ft_pf_putnbr(p->data.super);
	f->tmp = f->intlen;
	if (f->p2 > f->intlen)
		BRACKETS(f->intlen = f->p2, ((f->pos) ? f->intlen++ : 0));
	(f->neg > 0) ? fill(f, p, ' ') : 0;
	(f->p2 > f->tmp) ? f->intlen = f->tmp : 0;
	((f->p2 > f->width && f->ncheck == -1)) ? (p->ret++) : 0;
	(f->p2 > f->width && f->p2 > f->intlen) ? f->width = f->p2 : 0;
	IFELSE((f->width == 0), p->ret += f->len + f->intlen, p->ret += f->width);
}

void	i1(t_print *p, t_flags *f)
{
	if (f->ncheck == -1 && f->zero)
		ft_putchar('-');
	else if (f->pos && f->zero)
		BRACKETS(ft_putchar('+'), f->intlen++);
	f->tmp = f->intlen;
	(f->p2 > f->intlen) ? f->intlen = f->p2 : 0;
	(f->ncheck != -1 && f->pos && !f->zero && f->p2) ? f->intlen++ : 0;
	(f->neg == 0) ? fill(f, p, ' ') : 0;
	(f->p2 > f->tmp) ? f->intlen = f->tmp : 0;
	if (f->space && !f->pos)
		if ((f->p2 && f->p2 >= f->width) ||
							(!f->pos && f->ncheck != -1 && !f->width))
		{
			ft_putchar(' ');
			f->len++;
			(f->p2) ? p->ret++ : 0;
		}
}

void	ft_int(t_print *p, t_flags *f)
{
	f->len = 0;
	f->ncheck = 1;
	f->intlen = 0;
	int_data(p, f);
	if (f->width && f->space && f->zero && !f->p2)
		f->p2 = f->width - 1;
	if (check_zero(p, f, p->data.super_u) != 0)
		return ;
	(f->p2) ? f->zero = 0 : 0;
	if (p->data.super < 0)
	{
		p->data.super *= -1;
		f->ncheck = -1;
		f->intlen = 1;
		(f->p2 + 1 <= f->width) ? f->p2++ : 0;
	}
	f->intlen = f->intlen + ft_pf_intlen(p->data.super);
	(p->data.super < 0) ? f->intlen += 1 : 0;
	(f->intlen > f->width) ? f->width = 0 : 0;
	IF(f->p2 > f->intlen && (f->p2 > f->width),
				(f->width = f->p2 && f->zero++));
	i1(p, f);
	i2(p, f);
}
