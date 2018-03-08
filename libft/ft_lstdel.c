/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 19:16:40 by hasmith           #+#    #+#             */
/*   Updated: 2017/09/24 18:39:10 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Deletes the whole linked list
*/

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;
	t_list	*next;

	lst = *alst;
	while (lst)
	{
		next = lst->next;
		ft_lstdelone(&lst, del);
		lst = next;
	}
	*alst = NULL;
}
