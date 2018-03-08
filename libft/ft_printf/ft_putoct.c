/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:12:57 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 18:32:24 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putoct(uintmax_t nb, t_print *print, int cap)
{
	if (nb < 8 && cap == 0)
		ft_putchar(OCT[nb]);
	else if (nb < 16 && cap == 1)
		ft_putchar(OCT[nb + 8]);
	else
	{
		ft_putoct(nb / 8, print, cap);
		ft_putoct(nb % 8, print, cap);
	}
}

void	ft_octlen(uintmax_t nb, t_flags *flags)
{
	if (nb < 8)
		flags->intlen++;
	else
	{
		ft_octlen(nb / 8, flags);
		ft_octlen(nb % 8, flags);
	}
}
