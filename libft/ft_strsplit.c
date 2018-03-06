/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 19:11:57 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/25 14:29:10 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Splits the string delimited by char c and returns a NULL terminated array
*/

#include "libft.h"

static char		**ft_split(char **split, char *str, char c, size_t j)
{
	size_t		i;
	size_t		start;
	size_t		k;

	i = 0;
	start = 0;
	k = 0;
	while (str[i] != '\0' && k < j)
	{
		if (str[i] != c)
		{
			start = i;
			while (str[i] != c && str[i] != '\0')
				i++;
			split[k] = ft_strsub(str, start, i - start);
			k++;
		}
		else
			i++;
	}
	split[k] = NULL;
	return (split);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**split;
	size_t		k;

	if (!s)
		return (NULL);
	k = ft_cntstrwords((char*)s, c);
	split = NULL;
	if ((split = (char**)malloc((k + 1) * sizeof(char*))) == NULL)
		return (NULL);
	if (!split)
		return (NULL);
	split = ft_split(split, (char*)s, c, k);
	return (split);
}
