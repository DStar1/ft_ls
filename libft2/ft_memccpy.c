/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:05:29 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:37:08 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** copies bytes from memory area s2 into s1, stopping after the first
** occurrence of c has been copied, or after n bytes have been copied
*/

#include "libft.h"

void						*ft_memccpy(
		void *dest,
		const void *src,
		int c,
		size_t n)
{
	size_t					i;
	unsigned char			*cast_dest;
	unsigned char			cast_c;
	const unsigned char		*cast_src;

	i = 0;
	cast_dest = (unsigned char *)dest;
	cast_c = (unsigned char)c;
	cast_src = (const unsigned char *)src;
	while (i < n)
	{
		cast_dest[i] = cast_src[i];
		if (cast_dest[i] == cast_c)
			return ((dest + i + 1));
		i++;
	}
	return (NULL);
}
