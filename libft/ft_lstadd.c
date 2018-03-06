/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 19:15:23 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:38:09 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new link to a linked list
*/

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst && *alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
	else if ((!(*alst) || !alst) && new)
		*alst = new;
}
