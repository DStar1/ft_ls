/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:08:20 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:41:16 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** appends the string pointed to by src to the end of
** the string pointed to by dest up to n characters long.
*/

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = ft_strlen(dest);
	while (i < n && src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}
