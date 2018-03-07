/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:07:40 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 20:22:46 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** appends the string pointed to by src to the
** end of the string pointed to by dest.
*/

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t i;
	size_t j;

	i = 0;
	j = ft_strlen(dest);
	while (i < ft_strlen(src))
	{
		dest[j++] = src[i++];
	}
	dest[j] = '\0';
	return (dest);
}
