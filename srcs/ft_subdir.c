/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:30:25 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/03 15:52:54 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*construct_path(char *path, char *name)
{
	char *newpath;

	if (ft_strlen(path) > 0)
	{
		newpath = ft_strdup(path);
		if (path[ft_strlen(path) - 1] != '/')
			newpath = ft_strjoin_clr_1st(newpath, "/");
		newpath = ft_strjoin_clr_1st(newpath, name);
		return (newpath);
	}
	return (NULL);
}

/*
** print tree in alpha order
*/

void	subdir(t_bi *tree, char *path, int indent, t_lsargs *args)
{
	char *path1;

	if (tree == NULL)
		return ;
	args->first = 1;
	if (args->r)
		subdir(tree->right, path, indent, args);
	else
		subdir(tree->left, path, indent, args);
	if (tree->dir)
	{
		if (ft_strcmp(tree->d_name, ".") && ft_strcmp(tree->d_name, ".."))
		{
			args->maj_min_len = 0;
			args->device = 0;
			path1 = construct_path(path, tree->d_name);
			ft_printf("\n%s:\n", path1);
			listdir(path1, indent, args);
			free(path1);
		}
	}
	if (args->r)
		subdir(tree->left, path, indent, args);
	else
		subdir(tree->right, path, indent, args);
}
