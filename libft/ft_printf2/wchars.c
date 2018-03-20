/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:34:56 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/05 21:08:17 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*big_bytes(char *str, int c, int *i)
{
	if (c <= 0xFFFF)
	{
		str[0] = (c >> 12) | 0xE0;
		str[1] = ((c >> 6) & 0x3F) | 0x80;
		str[2] = (c & 0x3F) | 0x80;
		i += 3;
	}
	else if (c <= 0x10FFFF)
	{
		str[0] = (c >> 18) | 0xF0;
		str[1] = ((c >> 12) & 0x3F) | 0x80;
		str[2] = ((c >> 6) & 0x3F) | 0x80;
		str[3] = (c & 0x3F) | 0x80;
		i += 4;
	}
	return (str);
}

int		wchar_convert(int c)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strnew(4);
	if (c <= 0x80)
	{
		i++;
		str[0] = c;
	}
	else if (c <= 0x7FF)
	{
		str[0] = (c >> 6) | 0xC0;
		str[1] = (c & 0x3F) | 0x80;
		i += 2;
	}
	else if (c <= 0xFFFF)
		str = big_bytes(str, c, &i);
	else if (c <= 0x10FFFF)
		str = big_bytes(str, c, &i);
	ft_putstr(str);
	free(str);
	return (i);
}

void	ft_wchar(t_print *print, t_flags *flags)
{
	(void)flags;
	print->data.wc = va_arg(print->ap, wchar_t);
	print->ret += wchar_convert(print->data.wc);
	return ;
}

void	ft_wchar_string(t_print *print, t_flags *flags)
{
	int i;

	i = 0;
	(void)flags;
	print->data.wstr = va_arg(print->ap, wchar_t*);
	if (!print->data.wstr)
	{
		ft_putstr("(null)");
		print->ret += 6;
		return ;
	}
	while (print->data.wstr[i])
	{
		print->ret += wchar_convert(print->data.wstr[i]);
		i++;
	}
	return ;
}
