/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:08:04 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/02 18:41:11 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** allocates sufficient memory for a copy of the string
** s1, does the copy, and returns a pointer to it.
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *cpy;

	cpy = NULL;
	cpy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (cpy != NULL)
		ft_strcpy(cpy, s1);
	return (cpy);
}
