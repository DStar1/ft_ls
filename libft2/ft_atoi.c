/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:19:58 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:34:22 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts string to int
*/

#include "libft.h"

int		ft_atoi(char *str)
{
	int	i;
	int	is_neg;
	int	number;

	i = 0;
	is_neg = 1;
	number = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		is_neg = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		number *= 10;
		number += ((int)str[i] - 48);
		i++;
	}
	return (number * is_neg);
}
