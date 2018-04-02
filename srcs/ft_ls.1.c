/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:34:14 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/01 22:23:13 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** listdir while loop helper
** Checks to see if file is directory of not
** hides the . directories unless -a flag
*/

int		listdir_loop(char *path, t_lsargs **args, struct dirent *entry, t_bi **tree)
{
	struct stat	file_info;
	char		*path2;

	path2 = NULL;
	path2 = construct_path(path, entry->d_name);
	lstat(path2, &file_info);
	(*args)->time = file_info.st_mtime;
	(*args)->nsec = file_info.st_mtimespec.tv_nsec;
	if (S_ISBLK(file_info.st_mode) || S_ISCHR(file_info.st_mode))
		(*args)->device = 1;
	if (!(!(*args)->a && ft_strncmp(entry->d_name, ".", 1) == 0))
	{
		if ((*args)->size_len < file_info.st_size)//count the blocks
			(*args)->size_len = file_info.st_size;
		if ((*args)->size_links < ft_intlen(file_info.st_nlink))
			(*args)->size_links = ft_intlen(file_info.st_nlink);
		if ((*args)->minor_len < ft_intlen(minor(file_info.st_rdev)))
			(*args)->minor_len = ft_intlen(minor(file_info.st_rdev));
		if ((*args)->major_len < ft_intlen(major(file_info.st_rdev)))
			(*args)->major_len = ft_intlen(major(file_info.st_rdev));
		if ((*args)->device)
			(*args)->maj_min_len = (*args)->user_len + (*args)->group_len;
		(*args)->blocks += file_info.st_blocks;
	}
	if ((*args)->user_len < ft_strlen((*getpwuid(file_info.st_uid)).pw_name))
		(*args)->user_len = ft_strlen((*getpwuid(file_info.st_uid)).pw_name);
	if ((*args)->group_len < ft_strlen((*getgrgid(file_info.st_gid)).gr_name))
		(*args)->group_len = ft_strlen((*getgrgid(file_info.st_gid)).gr_name);
	if (!(*args)->a && ft_strncmp(entry->d_name, ".", 1) == 0)
	{
		free(path2);
		return (1);
	}
	if (S_ISDIR(file_info.st_mode))
		set_first_node(tree, entry, *args, 1);
	else
		set_first_node(tree, entry, *args, 0);
	free(path2);
	return (0);
}

/*
** Prints and resets
** 	///////set lengths back to zero for next directory padding////
** ft_printf("%s:\n", (args->all_paths)[args->i]);// srcs/:????????
*/

void	print_reset(t_lsargs *args, t_bi *tree, char *path)
{
	args->size_len = ft_intlen(args->size_len);
	if ((args->first == 0 && args->p > 1) || (args->p > 1 && !args->c_r))
		ft_printf("%s:\n", (args->all_paths)[args->i]);
	if (args->l)
		ft_printf("total %d\n", args->blocks);
	args->blocks = 0;
	if (args->r)
		print_binary_rev(tree, path, args);
	else
		print_binary(tree, path, args);
	args->size_len = 0;
	args->size_links = 0;
	args->group_len = 0;
	args->user_len = 0;
	args->minor_len = 0;
	args->major_len = 0;
	args->maj_min = 0;
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

	ft_bzero(&tree, sizeof(&tree));
	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)) != NULL)
		{
			args->major = 0;
			args->minor = 0;
			listdir_loop(path, &args, entry, &tree);
		}
		print_reset(args, tree, path);
		closedir(dir);
	}
	else
	{
		perror(ft_strjoin("ft_ls: ", path));
		args->error = 1;
	}
	if (args->c_r)
		subdir(tree, path, indent, args);
	free_binary(tree);
}
