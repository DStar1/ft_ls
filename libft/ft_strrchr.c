/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:08:57 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:41:32 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** searches for the last occurrence of the character c
** (an unsigned char) in the string pointed to, by the argument str.
*/

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	if (ft_strchr(str, c) == NULL)
		return (NULL);
	while (*str)
		str++;
	while (*str != c)
		str--;
	return ((char*)str);
}
