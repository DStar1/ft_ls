/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:34:14 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/06 00:23:38 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** listdir_loop helper
** count the blocks
*/

void	loop_helper(struct stat	*f_i,
					t_lsargs **args)
{
	if (!(!(*args)->a && ft_strncmp((*args)->d_name, ".", 1) == 0))
	{
		if ((*args)->size_len < f_i->st_size)
			(*args)->size_len = f_i->st_size;
		if ((*args)->size_links < ft_intlen(f_i->st_nlink))
			(*args)->size_links = ft_intlen(f_i->st_nlink);
		if ((*args)->minor_len < ft_intlen(minor(f_i->st_rdev)))
			(*args)->minor_len = ft_intlen(minor(f_i->st_rdev));
		if ((*args)->major_len < ft_intlen(major(f_i->st_rdev)))
			(*args)->major_len = ft_intlen(major(f_i->st_rdev));
		if ((*args)->device)
			(*args)->maj_min_len = (*args)->user_len + (*args)->group_len;
		(*args)->blocks += f_i->st_blocks;
	}
	if ((*args)->user_len < (int)ft_strlen((*getpwuid(f_i->st_uid)).pw_name))
		(*args)->user_len = (int)ft_strlen((*getpwuid(f_i->st_uid)).pw_name);
	if ((*args)->group_len < (int)ft_strlen((*getgrgid(f_i->st_gid)).gr_name))
		(*args)->group_len = (int)ft_strlen((*getgrgid(f_i->st_gid)).gr_name);
}

/*
** listdir while loop helper
** Checks to see if file is directory of not
** hides the . directories unless -a flag
*/

int		listdir_loop(char *path,
					t_lsargs **args,
					t_bi **tree,
					int one)
{
	struct stat	file_info;
	char		*path2;

	path2 = NULL;
	path2 = (!one) ? construct_path(path, (*args)->d_name) : path;
	lstat(path2, &file_info);
	(*args)->time = file_info.st_mtime;
	(*args)->nsec = file_info.st_mtimespec.tv_nsec;
	if (S_ISBLK(file_info.st_mode) || S_ISCHR(file_info.st_mode))
		(*args)->device = 1;
	((*args)->l) ? loop_helper(&file_info, args) : 0;
	if (!(*args)->a && ft_strncmp((*args)->d_name, ".", 1) == 0)
	{
		(!one) ? free(path2) : 0;
		// free(file_info);
		return (1);
	}
	if (S_ISDIR(file_info.st_mode))
		set_first_node(tree, *args, 1);
	else
		set_first_node(tree, *args, 0);
	(!one) ? free(path2) : 0;
	// free(file_info);
	return (0);
}

/*
** Main helper
** Print then reset
** Set lengths back to zero for next directory padding
*/

void	print_reset(char *path, t_bi *tree, t_lsargs *args, int one)
{
	args->size_len = ft_intlen(args->size_len);
	if (args->l && !one)
		ft_printf("total %d\n", args->blocks);
	args->blocks = 0;
	if (!args->r || one)
		print_binary(tree, path, args, one);
	else
		print_binary_rev(tree, path, args);
	args->size_len = 0;
	args->size_links = 0;
	args->group_len = 0;
	args->user_len = 0;
	args->minor_len = 0;
	args->major_len = 0;
	args->maj_min = 0;
}

/*
** If arg is not directory
*/

void	listdir_else(char *path,
					struct stat *file_info,
					t_lsargs *args,
					t_bi *tree)
{
	if (lstat(path, file_info) == 0)
	{
		args->d_name = ft_strdup(path);
		args->one = 1;
		listdir_loop(path, &args, &tree, 1);
		free(args->d_name);
		print_reset(path, tree, args, 1);
	}
	else
	{
		perror(ft_strjoin("ft_ls: ", path));
		args->error = 1;
	}
}

/*
** Loop through names and then print the binary tree
** If -R flag, goes through binary tree and finds all
** directories and does listdir for each
*/

void	listdir(char *path, int indent, t_lsargs *args)
{
	DIR				*dir;
	struct dirent	*entry;
	t_bi			*tree;
	struct stat		file_info;

	ft_bzero(&tree, sizeof(&tree));
	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)) != NULL)
		{
			args->major = 0;
			args->minor = 0;
			args->d_name = ft_strdup(entry->d_name);
			listdir_loop(path, &args, &tree, 0);
			free(args->d_name);
		}
		print_reset(path, tree, args, 0);
		closedir(dir);
	}
	else
		listdir_else(path, &file_info, args, tree);
	if (args->c_r)
		subdir(tree, path, indent, args);
	free_binary(tree);
}
