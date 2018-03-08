/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:08:49 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/25 13:53:09 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** function locates the	first occurrence of the	null-termi-
** nated string little in the	string big, where not more than	len characters
** are searched.
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*lil_ptr;
	const char	*big_ptr;
	size_t		lil_len;
	size_t		big_len;

	if (*little == '\0')
		return ((char*)big);
	lil_len = ft_strlen(little);
	big_len = ft_strlen(big);
	while (len-- >= lil_len && big_len-- >= lil_len)
	{
		lil_ptr = little;
		big_ptr = big;
		while (*lil_ptr++ == *big_ptr++)
		{
			if (*lil_ptr == '\0')
				return ((char*)big);
		}
		big++;
	}
	return (NULL);
}
