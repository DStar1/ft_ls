/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:30:25 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/18 22:00:06 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** print tree in alpha order
*/

void	subdir(t_bi *tree, char **path, int indent, t_lsargs *args)
{
	char *path1;///////////////////////free?
	
	if (tree == NULL)
		return ;
	subdir(tree->left, path, indent, args);
	if (tree->dir)//tree->d_type == 4)
	{

		// if (!ft_strcmp(pt->d_name, ".")||!ft_strcmp(pt->d_name, "..")) continue;
		// strcpy(path, dir);
		// if (path[ft_strlen(path)-1]!='/')
		// {
		// 	ft_strcat(path, "/");
		// 	ft_strcat(path, tree->d_name);
		// }

        path1 = ft_strjoin(*path, "/");
        path1 = ft_strjoin_clr_1st(path1, tree->d_name);//////////////////////////////////////////////////free?
        ft_printf("\n%s\n", path1);

		// snprintf(path1, sizeof(path1), "%s/%s", path, tree->d_name);//make new path
		// printf("       %s Path: %s\n", tree->d_name, path1);
		
		listdir(&path1, indent, args);
	}
	// ft_printf("%s\n", tree->d_name);
	subdir(tree->right, path, indent, args);
}
