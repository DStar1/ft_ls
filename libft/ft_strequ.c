/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 15:14:50 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:40:44 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** comparison between s1 and s2. If the 2 strings
** are identical the function returns 1, or 0 otherwise.
*/

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (ft_strcmp(s1, s2) == 0)
		return (1);
	return (0);
}
