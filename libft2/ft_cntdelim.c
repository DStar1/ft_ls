/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntdelim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 00:17:53 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 15:30:03 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cntdelim(const char *str, int c)
{
	int i;
	int cnt;
	int last;

	last = 0;
	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (last == 0 && str[i] == c)
		{
			cnt++;
			last = 1;
		}
		if (str[i] != c)
			last = 0;
		i++;
	}
	return (cnt);
}
