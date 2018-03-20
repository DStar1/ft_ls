/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:08:04 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/19 17:25:18 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** allocates sufficient memory for a copy of the string
** s1, does the copy, and returns a pointer to it.
*/

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*cpy;

	i = 0;
	len = ft_strlen((char*)str);
	cpy = (char*)malloc((len + 1) * sizeof(*str));
	if (cpy == NULL)
		return (NULL);
	cpy[len + 1] = '\0';
	while (i <= len)
	{
		cpy[i] = str[i];
		i++;
	}
	return (cpy);
}
