/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:05:55 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:37:49 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Searches for the first occurrence of the character c (an unsigned char)
** in the first n bytes of the string pointed to, by the argument str
*/

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cast_c;
	unsigned char	*cast_s;

	i = -1;
	cast_c = (unsigned char)c;
	cast_s = (unsigned char *)s;
	while (++i < n)
		if (cast_s[i] == cast_c)
			return ((void *)cast_s + i);
	return (NULL);
}
