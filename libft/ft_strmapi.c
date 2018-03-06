/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 13:18:34 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:22:14 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies the function f to each character of the string passed
** as argument by giving its index as first argument to create a
** “fresh” new string (with malloc(3)) resulting from the successive
** applications of f.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*fresh;
	char	*save_fresh;
	char	*save_src;
	size_t	size;
	int		i;

	if (s && f)
	{
		size = ft_strlen((char *)s);
		fresh = (char *)malloc((size + 1) * sizeof(char));
		if (fresh == NULL)
			return (NULL);
		save_fresh = fresh;
		save_src = (char *)s;
		i = 0;
		while (*save_src)
		{
			*fresh = (*f)(i, (char)*save_src++);
			fresh++;
			i++;
		}
		*fresh = '\0';
		return (save_fresh);
	}
	return (NULL);
}
