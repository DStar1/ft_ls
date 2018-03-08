/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:09:03 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/26 17:14:25 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns pointer to first occurrence of needle in haystack
*/

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	unsigned int	i;
	unsigned int	pos;
	size_t			len;

	i = 0;
	len = ft_strlen((char*)needle);
	if (len == 0)
		return ((char*)haystack);
	while (haystack[i])
	{
		pos = 0;
		while (needle[pos] == haystack[pos + i])
		{
			if (pos == (len - 1))
				return ((char*)haystack + i);
			pos++;
		}
		i++;
	}
	return (NULL);
}
