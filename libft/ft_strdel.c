/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:07:57 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:40:11 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Takes as a parameter the address of a string that
** need to be freed with free(3), then sets its pointer to NULL.
*/

#include "libft.h"

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = 0;
	}
}
