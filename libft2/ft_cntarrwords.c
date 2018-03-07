/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntarrwords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 12:24:58 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:33:26 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Counts words in an array
*/

#include "libft.h"

int		ft_cntarrwords(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
