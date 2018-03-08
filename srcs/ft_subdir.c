/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:30:25 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/08 01:46:18 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** print tree in alpha order
*/

void	subdir(t_bi *tree, char *path, int indent)
{
	char *path1;///////////////////////free?
	
	if (tree == NULL)
		return ;
	subdir(tree->left, path, indent);
	if (tree->dir)
	{
        path1 = ft_strjoin(path, "/");
        path1 = ft_strjoin_clr_1st(path1, tree->d_name);//////////////////////////////////////////////////free?
        printf("    %s, Path: %s\n", tree->d_name, path1);
		// snprintf(path1, sizeof(path1), "%s/%s", path, tree->d_name);//make new path
		// printf("%*s[%s]: Path: %s\n", indent, "", tree->d_name, path1);
		listdir(path1, indent);
	}
	// ft_printf("%s\n", tree->d_name);
	subdir(tree->right, path, indent);
}