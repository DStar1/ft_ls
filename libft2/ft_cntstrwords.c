/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntstrwords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 12:19:24 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/26 16:39:20 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Counts amount of words separated by the char c
*/

#include "libft.h"

size_t		ft_cntstrwords(char *str, char c)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			k++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (k);
}
