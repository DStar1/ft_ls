/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 12:33:14 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:00:33 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Counts elements in linked list
*/

#include "libft.h"

int		ft_lstsize(t_list *begin_list)
{
	int		count;
	t_list	*list;

	list = begin_list;
	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}
