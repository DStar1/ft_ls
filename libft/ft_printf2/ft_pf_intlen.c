/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_intlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 01:06:30 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 18:13:14 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Counts the length of an int
*/

#include "ft_printf.h"

int		ft_pf_intlen(uintmax_t n)
{
	uintmax_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
