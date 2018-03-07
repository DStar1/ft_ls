/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 01:06:30 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:35:00 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Counts the length of an int
*/

#include "libft.h"

int		ft_intlen(int n)
{
	unsigned int	len;

	if (n == 0)
		return (1);
	len = (n < 0) ? 1 : 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
