/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 19:05:30 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 19:55:05 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			set_flags(t_flags *flags)
{
	flags->hash = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->neg = 0;
	flags->pos = 0;
	flags->perc = 0;
	flags->width = 0;
	flags->l = 0;
	flags->ll = 0;
	flags->hh = 0;
	flags->h = 0;
	flags->j = 0;
	flags->z = 0;
	flags->p = 0;
	flags->p1 = 0;
	flags->p2 = 0;
	flags->intlen = 0;
	flags->ncheck = 0;
}

int				pf_atoi(t_print *p)
{
	int start;
	int nb;

	nb = 0;
	start = p->i;
	while (p->fmt[p->i] && ft_isdigit(p->fmt[p->i]))
	{
		nb += (p->fmt[p->i] - '0');
		nb *= 10;
		p->i++;
	}
	if (p->i > start)
		nb /= 10;
	return (nb);
}

int				res_flags(char c)
{
	if ((c == 's') || (c == 'S'))
		return (1);
	else if ((c == 'd') || (c == 'i') || (c == 'D')
	|| (c == 'o') || (c == 'O') || (c == 'u')
	|| (c == 'U'))
		return (2);
	else if ((c == 'x') || (c == 'X'))
		return (3);
	else if ((c == 'p') || (c == 'c') || (c == 'C')
	|| (c == '%'))
		return (4);
	else if (c == 'b' || c == 'n')
		return (5);
	return (0);
}
