/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 12:40:36 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:32:23 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Prints out a string array
*/

#include "libft.h"

void	ft_putarr(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putstr((const char *)str[i]);
		ft_putchar('\n');
		i++;
	}
}
