/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:07:44 by hasmith           #+#    #+#             */
/*   Updated: 2017/10/31 16:42:11 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** searches for the first occurrence of the character c
** (an unsigned char) in the string pointed to by the argument str.
*/

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*str1;

	str1 = (char *)str;
	while (*str1 != c)
	{
		if (*str1 == '\0')
		{
			return (NULL);
		}
		str1++;
	}
	return (str1);
}
