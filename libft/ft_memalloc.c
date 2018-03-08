/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:04:44 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:45:14 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a “fresh” memory area
*/

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!size)
		return (NULL);
	mem = (void *)malloc(sizeof(void*) * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
