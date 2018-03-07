/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 17:16:54 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/06 16:26:55 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a “fresh” string
** ending with ’\0’, result of the concatenation of s1 and s2.
*/

#include "libft.h"

static char	*ft_strloop(char const *s1, char const *s2, int s1_len, int s2_len)
{
	char	*fresh;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((fresh = ft_strnew(s1_len + s2_len)) == NULL)
		return (NULL);
	while ((i + j) < (s1_len + s2_len))
	{
		if (i < s1_len)
		{
			fresh[i] = s1[i];
			i++;
		}
		else
		{
			fresh[i + j] = s2[j];
			j++;
		}
	}
	fresh[j + i] = '\0';
	return (fresh);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	int		s1_len;
	int		s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	fresh = ft_strloop(s1, s2, s1_len, s2_len);
	if (fresh == NULL)
		return (NULL);
	return (fresh);
}
