/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:37:40 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:37:07 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts int to string
*/

#include "libft.h"

static int		ft_size(int n)
{
	int i;
	int nb;

	i = 0;
	nb = n;
	if (n < 0)
	{
		i++;
		nb = -n;
	}
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static void		ft_fill(char *cp, int i, int abs, int n)
{
	while (i >= 0)
	{
		if (i == 0 && n < 0)
		{
			cp[i] = '-';
		}
		else
		{
			cp[i] = (abs % 10) + '0';
			abs = abs / 10;
		}
		i--;
	}
}

char			*ft_itoa(int n)
{
	char	*cp;
	int		t;
	int		abs;
	int		i;

	t = ft_size(n);
	cp = NULL;
	cp = (char *)malloc(sizeof(char) * (t + 1));
	abs = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (cp == NULL)
		return (NULL);
	i = t;
	cp[i] = '\0';
	i--;
	if (n < 0)
	{
		abs = -n;
	}
	ft_fill(cp, i, abs, n);
	return (cp);
}
