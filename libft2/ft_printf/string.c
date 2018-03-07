/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 21:00:43 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 19:14:30 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		s_if_else(t_print *print, t_flags *flags)
{
	if (flags->width)
	{
		if (flags->neg)
		{
			ft_putstr(print->data.str);
			fill(flags, print, ' ');
		}
		else
		{
			fill(flags, print, ' ');
			ft_putstr(print->data.str);
		}
		print->ret += flags->width;
	}
	else
	{
		ft_putstr(print->data.str);
		print->ret += flags->intlen;
	}
}

void			ft_string(t_print *print, t_flags *flags)
{
	print->data.str = va_arg(print->ap, char *);
	if ((flags->p && print->data.str == NULL) || (flags->p && !flags->p2))
	{
		fill(flags, print, ' ');
		print->ret += flags->width;
	}
	else
	{
		IF(print->data.str == NULL, print->data.str = "(null)");
		if (flags->p2)
			print->data.str = ft_strsub(print->data.str, 0, flags->p2);
		flags->intlen = ft_strlen(print->data.str);
		(flags->intlen > flags->width) ? flags->width = flags->intlen : 0;
		if (flags->p && !flags->p2)
		{
			print->data.str = "";
			flags->intlen = 0;
		}
		s_if_else(print, flags);
	}
}

void			ft_char(t_print *print, t_flags *flags)
{
	print->data.i = va_arg(print->ap, int);
	flags->intlen = 1;
	if (flags->width)
	{
		if (flags->neg)
		{
			ft_putchar(print->data.i);
			fill(flags, print, ' ');
		}
		else
		{
			fill(flags, print, ' ');
			ft_putchar(print->data.i);
		}
		print->ret += flags->width;
	}
	else
	{
		ft_putchar(print->data.i);
		print->ret += flags->intlen;
	}
}
