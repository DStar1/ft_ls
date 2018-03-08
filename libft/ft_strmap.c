/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 13:18:34 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:21:35 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies the function f to each character of the string given
** as argument to create a “fresh” new string (with malloc(3))
** resulting from the successive applications of f.
*/

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fresh;
	char	*save_fresh;
	char	*save_src;
	size_t	size;

	if (s && f)
	{
		size = ft_strlen((char *)s);
		fresh = (char *)malloc((size + 1) * sizeof(char));
		if (fresh == NULL)
			return (NULL);
		save_fresh = fresh;
		save_src = (char *)s;
		while (*save_src)
		{
			*fresh = (*f)((char)*save_src);
			save_src++;
			fresh++;
		}
		*fresh = '\0';
		return (save_fresh);
	}
	return (NULL);
}
