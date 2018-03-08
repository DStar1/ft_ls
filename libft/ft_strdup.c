/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:08:04 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:40:33 by hasmith          ###   ########.fr       */
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
	int		strlen;
	char	*strdup;

	i = 0;
	strlen = ft_strlen((char*)str);
	strdup = (char*)malloc((strlen + 1) * sizeof(*str));
	if (strdup == NULL)
		return (NULL);
	strdup[strlen + 1] = '\0';
	while (i <= strlen)
	{
		strdup[i] = str[i];
		i++;
	}
	return (strdup);
}
