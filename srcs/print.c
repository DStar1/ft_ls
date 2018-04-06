/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 23:37:54 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/06 03:03:16 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	setdata2(t_lsargs *args, struct stat *file_info)
{
	// int i;
	// int j;
	//segfaults at YO2 ./ft_ls -l /Library/Scripts/42 
			// ft_printf("YO\n");
	args->perms = permissions(file_info->st_mode, args);
				// ft_printf("YO2\n");
	args->pw_name = (*getpwuid(file_info->st_uid)).pw_name;
				// ft_printf("YO3\n");
	args->gr_name = (*getgrgid(file_info->st_gid)).gr_name;
				// ft_printf("YO4\n");
	args->links = file_info->st_nlink;
				// ft_printf("YO5\n");
	args->size = file_info->st_size;
				// ft_printf("YO6\n");
}

/*
** set data for dash l
*/

int		setdata(t_bi *tree, char *path, t_lsargs *args, int one)
{
	struct stat file_info;
	char		*np;
	char		buf[1024];
	ssize_t		len;

	(args->month_time) ? free(args->month_time) : 0;
	np = (!one) ? construct_path(path, tree->d_name, args) : tree->d_name;
	suffix(np, args);
	lstat(np, &file_info);
	setdata2(args, &file_info);
	args->ctime = ctime(&tree->time);
	args->month_time = ft_strsub(args->ctime, 4, 12);
	ft_bzero(buf, sizeof(buf));
	if (args->fd && (len = readlink(np, buf, sizeof(buf))) != -1)
		ft_strcpy(args->link_path, buf);
	if (S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode))
	{
		args->major = major(file_info.st_rdev);
		args->minor = minor(file_info.st_rdev);
		args->maj_min = 1;
	}
	else
		args->maj_min = 0;
	(!one) ? free(np) : 0;
	return (0);
}

/*
** Print dash l
*/

void	print_l(t_bi *tree, char *path, t_lsargs *a, int one)
{
	setdata(tree, path, a, one);
	ft_printf("%s %*d %-*s  %-*s  ", a->perms, a->size_links, a->links, a->
				user_len, a->pw_name, a->group_len, a->gr_name);
	if (a->maj_min && a->minor_len >= a->size_len)
		ft_printf(" %*d, %*d", a->major_len, a->major, a->minor_len, a->minor);
	else if (a->maj_min && a->minor_len < a->size_len)
		ft_printf(" %*d, %*d", a->major_len,
		a->major, a->size_len - 1, a->minor);
	else if (a->device && a->minor_len >= a->size_len)
		ft_printf(" %*d", a->major_len + a->minor_len + 2, a->size);
	else if ((a->device) && a->minor_len < a->size_len)
		ft_printf(" %*d", a->major_len + a->size_len + 1, a->size);
	else
		ft_printf("%*d", a->size_len, a->size);
	ft_printf(" %s %s", a->month_time, tree->d_name);
	if (a->fd)
	{
		ft_printf(" -> %s", a->link_path);
		a->fd = 0;
	}
	ft_putchar('\n');
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
		print_l(tree, path, args, 0);
	else
		ft_printf("%s\n", tree->d_name);
	print_binary_rev(tree->left, path, args);
}

/*
** print tree in alpha order
*/

void	print_binary(t_bi *tree, char *path, t_lsargs *args, int one)
{
	int intlen;

	intlen = 0;
	if (tree == NULL)
		return ;
	print_binary(tree->left, path, args, one);
	if (args->l)
		print_l(tree, path, args, one);
	else
		ft_printf("%s\n", tree->d_name);
	print_binary(tree->right, path, args, one);
}
