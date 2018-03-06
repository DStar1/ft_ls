/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:07:48 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 19:10:30 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** compares the string pointed to, by str1 to the string pointed to by str2.
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
