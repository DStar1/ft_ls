/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 20:20:44 by hasmith           #+#    #+#             */
/*   Updated: 2017/12/08 19:19:09 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_hextoi(char *hex)
{
	int val;
	int i;

	val = 0;
	i = 0;
	while (hex[i])
	{
		if (hex[i] == 'x')
			i++;
		if (hex[i] >= '0' && hex[i] <= '9')
			hex[i] = hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			hex[i] = hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			hex[i] = hex[i] - 'A' + 10;
		val = (val << 4) | (hex[i]);
		i++;
	}
	return (val);
}
