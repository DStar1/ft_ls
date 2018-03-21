/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 23:37:54 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/20 23:48:30 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** print tree in alpha order
*/

void	free_binary(t_bi *tree)
{
	if (tree == NULL)
		return ;
	free_binary(tree->left);
	free_binary(tree->right);
	free(tree->d_name);
	free(tree);
}

/*
** set data for dash l
*/

int	setdata(t_bi *tree, char *path, t_lsargs *args)
{
	struct stat file_info;
	char *lstatpath;

	if (args->month_time)
		free(args->month_time);
	lstatpath = construct_path(path, tree->d_name);
	lstat(lstatpath, &file_info);
	args->permissions = permissions(file_info.st_mode, args);
	args->user = *getpwuid(file_info.st_uid);
	args->group = *getgrgid(file_info.st_gid);
	args->ctime = ctime(&tree->time);
	args->month_time = ft_strsub(args->ctime, 4, 12);
	args->links = file_info.st_nlink;
	args->size = file_info.st_size;
	free(lstatpath);
	return (0);
}

/*
** print tree in reverse alpha order
*/

void	print_binary_rev(t_bi *tree, char *path, t_lsargs *args)
{
	if (tree == NULL)
		return ;
	print_binary_rev(tree->right, path, args);
	if (args->l)
	{
		setdata(tree, path, args);
		ft_printf("%s  %d %s  %s  %*d %s %s\n", args->permissions, args->links, args->user.pw_name, args->group.gr_name, args->size_len, args->size, args->month_time, tree->d_name);
	}
	else
		ft_printf("%s\n", tree->d_name);
	print_binary_rev(tree->left, path, args);
}

/*
** print tree in alpha order
*/

void	print_binary(t_bi *tree, char *path, t_lsargs *args)
{
	int intlen;

	intlen = 0;
	if (tree == NULL)
		return ;
	print_binary(tree->left, path, args);
	if (args->l)
	{
		setdata(tree, path, args);
		ft_printf("%s  %d %s  %s  %*d %s %s\n", args->permissions, args->links, args->user.pw_name, args->group.gr_name, args->size_len, args->size, args->month_time, tree->d_name);
	}
	else
		ft_printf("%s\n", tree->d_name);
	print_binary(tree->right, path, args);
}