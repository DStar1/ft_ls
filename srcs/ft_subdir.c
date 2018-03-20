/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:30:25 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/19 17:53:27 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*construct_path(char *path, char *name)
{
	char *newpath;

	// newpath = ft_strnew(0);// = NULL;newpath = NULL;
	if (ft_strlen(path) > 0)
	{
		newpath = ft_strnew(ft_strlen(path)+1);
		// ft_printf("Previous path in construct: %s\n", path);
		ft_memcpy(newpath, path, ft_strlen(path)+1);//newpath = ft_strdup(path);//ft_strcpy(newpath, path);////////
		// ft_printf("2Previous path in construct: %s\n", newpath);
		if (path[ft_strlen(path) - 1] != '/')
			newpath = ft_strjoin(path, "/");
		newpath = ft_strjoin_clr_1st(newpath, name);//////////////////////////////////////////////////free?
		// ft_printf("Newpath in construct: %s | Previous path in construct: %s\n", newpath, path);
		return (newpath);
	}
	// ft_printf("Newpath: %s\n", NULL);
	return (NULL);
}

/*
** print tree in alpha order
*/

void	subdir(t_bi *tree, char *path, int indent, t_lsargs *args)
{
	char *path1;///////////////////////free?

	if (tree == NULL)
		return ;
	subdir(tree->left, path, indent, args);
	if (tree->dir)// && ft_strcmp(tree->d_name, ".") && ft_strcmp(tree->d_name, ".."))//tree->d_type == 4)
	{

		if (ft_strcmp(tree->d_name, ".") != 0 && ft_strcmp(tree->d_name, "..") != 0)//hides the . directories (add -a flag check here)
		{		//return ;//if inverse is true

		// if (!ft_strcmp(pt->d_name, ".")||!ft_strcmp(pt->d_name, "..")) continue;
		// strcpy(path, dir);
		// if (path[ft_strlen(path)-1]!='/')
		// {
		// 	ft_strcat(path, "/");
		// 	ft_strcat(path, tree->d_name);
		// }

        // path1 = ft_strjoin(*path, "/");
        // path1 = ft_strjoin_clr_1st(path1, tree->d_name);//////////////////////////////////////////////////free?
		path1 = construct_path(path, tree->d_name);
        ft_printf("\n%s\n", path1);

		// snprintf(path1, sizeof(path1), "%s/%s", path, tree->d_name);//make new path
		// printf("       %s Path: %s\n", tree->d_name, path1);
		// ft_printf("Passing path1: %s, indent: %d, and args to listdir\n", path1, indent);
		listdir(path1, indent, args);
		free(path1);
		}
	}
	// ft_printf("%s\n", tree->d_name);
	subdir(tree->right, path, indent, args);
}
