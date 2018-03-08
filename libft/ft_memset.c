/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:06:30 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:39:04 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** copies the character c (an unsigned char) to the first
** n characters of the string pointed to, by the argument str.
*/

#include "libft.h"

void	*ft_memset(void *in, int data, size_t len)
{
	unsigned char *ptr;

	ptr = (unsigned char*)in;
	while (len-- > 0)
		*ptr++ = (unsigned char)data;
	return (in);
}
