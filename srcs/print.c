/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 23:37:54 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/22 00:54:00 by hasmith          ###   ########.fr       */
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
	if (args->fd)
		args->link_path = ft_strsub(realpath(lstatpath, NULL), ft_strlen(path) + 1, ft_strlen(realpath(lstatpath, NULL)) - ft_strlen(path));
	if (S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode))
	{
        args->major = major(file_info.st_rdev);
        args->minor = minor(file_info.st_rdev);
		args->maj_min = 1;
	}
	else
		args->maj_min = 0;
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
		ft_printf("%s  %*d %s  %s  %*d %s %s\n", args->permissions, args->size_links, args->links, args->user.pw_name, args->group.gr_name, args->size_len, args->size, args->month_time, tree->d_name);
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
		ft_printf("%s  %*d %-*s  %-*s  ", args->permissions, args->size_links, args->links, args->user_len, args->user.pw_name, args->group_len, args->group.gr_name, args->size_links);
		if (args->maj_min && !args->size_len)
			ft_printf(" %*d, %*d", args->major_len, args->major, args->minor_len, args->minor);
		else if (args->maj_min && args->size_len)
			ft_printf(" %*d, %*d", args->major_len, args->major, args->size_len - 1, args->minor);
		else if (args->device && !args->size_len)
			ft_printf(" %*d", args->major_len + args->minor_len + 2, args->size);
		else if (args->device && args->size_len)
			ft_printf(" %*d", args->major_len + args->size_len + 1, args->size);//////
		else
			ft_printf("%*d", args->size_len, args->size);
		ft_printf(" %s %s", args->month_time, tree->d_name);
		if (args->fd)
		{
			ft_printf(" -> %s", args->link_path);//fd/%d", args->fd_num);
			free(args->link_path);
			args->fd = 0;
		}
		ft_putchar('\n');
		// if (args->size == 4342)
		// 	ft_printf("%d\n", args->device);
	}
	else
		ft_printf("%s\n", tree->d_name);
	print_binary(tree->right, path, args);
}