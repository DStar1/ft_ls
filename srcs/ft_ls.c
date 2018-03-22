/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:34:14 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/22 01:05:47 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
//////////////////////////////////////////////////////////sometimes it segfaults on -R!!!!!!!!!!!!!!!!! the first time I go into recursive function/// path is wrong in recursion!!!!!!

/*
** listdir while loop helper
** Checks to see if file is directory of not
** hides the . directories unless -a flag
*/

int listdir_loop(char *path, t_lsargs **args, struct dirent *entry, t_bi **tree)
{
	struct stat file_info;
	char *path2;
	
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
	if ((*args)->user_len < ft_strlen((*getpwuid(file_info.st_uid)).pw_name))//////////
		(*args)->user_len = ft_strlen((*getpwuid(file_info.st_uid)).pw_name);
	if ((*args)->group_len < ft_strlen((*getgrgid(file_info.st_gid)).gr_name))//////////
		(*args)->group_len = ft_strlen((*getgrgid(file_info.st_gid)).gr_name);
	// if ((*args)->device)
	// 	(*args)->maj_min_len = (*args)->user_len + (*args)->group_len;
	if (S_ISDIR(file_info.st_mode))
	{
		if (!(*args)->a && ft_strncmp(entry->d_name, ".", 1) == 0)
			BRACKETS(free(path2), return (1));
		set_first_node(tree, entry, *args, 1);
	}
	else
		set_first_node(tree, entry, *args, 0);
	free(path2);
	return (0);
}

/*
** Loop through names and then print the binary tree
** If -R flag, goes through binary tree and finds all
** directories and does listdir for each
*/

void listdir(char *path, int indent, t_lsargs *args)
{
	DIR *dir;
	struct dirent *entry;
	t_bi *tree;

	ft_bzero(&tree, sizeof(&tree));
	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)) != NULL)
		{
			args->major = 0;
			args->minor = 0;
			listdir_loop(path, &args, entry, &tree);
		}
		args->size_len = ft_intlen(args->size_len);
		if ((args->first == 0 && args->p > 1) || (args->p > 1 && !args->c_r))
		{
			ft_printf("%s:\n", (args->all_paths)[args->i]);// srcs/:
		}
		if (args->l)
			ft_printf("total %d\n", args->blocks);
		args->blocks = 0;
		if (args->r)
			print_binary_rev(tree, path, args);
		else
			print_binary(tree, path, args);
		///////set lengths back to zero for next directory padding////
		args->size_len = 0;
		args->size_links = 0;
		args->group_len = 0;
		args->user_len = 0;
		args->minor_len = 0;
		args->major_len = 0;
		args->maj_min = 0;

		closedir(dir);
	}
	else
	{
    	perror (ft_strjoin("ft_ls: ", path));
		args->error = 1;
	}
	if (args->c_r)
		subdir(tree, path, indent, args);
	free_binary(tree);
}

/*
** Parsing args
*/

int parse_arg(char *str, t_lsargs *args)
{
	int i;

	i = 0;
	while (str[++i] != '\0')
	{
		str[i] == 'r' ? args->r = 1 : 0;
		str[i] == 'l' ? args->l = 1 : 0;
		str[i] == 't' ? args->t = 1 : 0;
		str[i] == 'R' ? args->c_r = 1 : 0;
		str[i] == 'a' ? args->a = 1 : 0;
		str[i] == '1' ? args->l = 0 : 0;
		if (str[i] != 'r' && str[i] != 'a' && str[i] != '1'
			&& str[i] != 'l' && str[i] != 't' && str[i] != 'R')
		{
			ft_printf("ft_ls: illegal option -- %c\n", str[i]);
			ft_printf("usage: ls [-alrRt1] [file ...]\n");
			// ft_printf("Try 'ft_ls --help' for more information.\n");
			args->error = 1;
			return (1);
		}
	}
	return (0);
}

void ft_strswap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void     ft_strsort(t_lsargs *args)
{
	int i;

	i = 0;
	while ((args->all_paths)[i + 1])
	{
		if (ft_strcmp((args->all_paths)[i], (args->all_paths)[i + 1]) > 0)
		{
			ft_strswap(&(args->all_paths[i]), &(args->all_paths[i + 1]));
			i = -1;
		}
		i++;
	}
}

int main(int ac, char **av)//test with /dev
{
	char **path;
	t_ls ls;
	t_lsargs args;


	ft_bzero(&args, sizeof(args));
	args.all_paths = (char**)ft_memalloc(sizeof(char*) * ac);
	args.p = 0;
	// ft_bzero(&path, sizeof(char*) * ac - 1);
	// path = NULL;
	int i = 1;
	while (i < ac)
	{
		// ft_printf("%d, %s\n", i, av[i]);
		if (!args.p && av[i][0] == '-' && av[i][1] != '\0')// && flags->endflag != 1)
		{
			parse_arg(av[i], &args);
		}
		else //if (i > 1)
		{
			(args.all_paths)[args.p++] = ft_strdup(av[i]);
		}
		i++;
	}
	// for (int i = 0; (args.all_paths)[i]; i++ )
	// 	ft_printf("%d, %s\n", i, (args.all_paths)[i]);
	if (args.error)
		exit (1);//add error message?
	if (!(args.all_paths)[0])
	{
		(args.all_paths)[0] = ".";
		listdir((args.all_paths)[args.i], 0, &args);
	}
	else
	{
		ft_strsort(&args);
		// for (int i = 0; (args.all_paths)[i]; i++ )
		// 	ft_printf("%d, %s\n", i, (args.all_paths)[i]);
		args.i = -1;
		while ((args.all_paths)[++args.i])
		{
			args.first = 0;
			listdir((args.all_paths)[args.i], 0, &args); //first arg is the path
			if (!args.error && args.p && args.i != args.p - 1)
				ft_putchar('\n');
			args.error = 0;
		}
	}
	// ft_printf("%s\n", path);
	// while (1)
	// 		;
	return (0);
}
