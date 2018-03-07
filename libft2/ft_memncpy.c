/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:06:11 by hasmith           #+#    #+#             */
/*   Updated: 2018/01/17 19:49:07 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** copies n characters from start index of memory area str2 to memory area str1
*/

#include "libft.h"

void	*ft_memncpy(void *s1, const void *s2, size_t start, size_t n)
{
	char	*c1;
	char	*c2;

	if (n == 0 || s1 == s2)
		return (s1);
	c1 = (char *)s1;
	c2 = (char *)s2 + start;
	while (--n)
		*c1++ = *c2++;
	*c1 = *c2;
	return (s1);
}
