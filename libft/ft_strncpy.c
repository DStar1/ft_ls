/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:08:36 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:24:50 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** copies up to n characters from the string pointed to, by src to dest.
*/

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	size_t i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
