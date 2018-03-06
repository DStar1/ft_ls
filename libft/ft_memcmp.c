/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:06:03 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:53:11 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** compares the first n bytes of memory area str1 and memory area str2.
*/

#include "libft.h"

int		ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	int				i;

	i = 0;
	src1 = (unsigned char *)str1;
	src2 = (unsigned char *)str2;
	while (n--)
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}
