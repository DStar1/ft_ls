/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 21:44:20 by hasmith           #+#    #+#             */
/*   Updated: 2018/11/14 15:11:29 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Parsing args
*/

int		parse_arg(char *str, t_lsargs *args)
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
			args->error = 1;
			return (1);
		}
	}
	return (0);
}

/*
** Goes through binary tree of args based on alphabetical serch
** If not reverse start left and go right, else inverse
*/

void	args_binary(t_bi *tree, t_lsargs *args, int dir)
{
	if (tree == NULL)
		return ;
	(!args->r) ? args_binary(tree->left, args, dir)
				: args_binary(tree->right, args, dir);
	if (tree->dir == dir)
	{
		args->dir_main = dir;
		(dir && args->first) ? ft_putchar('\n') : 0;
		(!args->dir_name) ? free(args->dir_name) : 0;
		args->dir_name = ft_strdup(tree->d_name);
		args->first = 0;
		listdir(tree->d_name, 0, args);
		args->error = 0;
		args->first++;
	}
	(!args->r) ? args_binary(tree->right, args, dir)
				: args_binary(tree->left, args, dir);
}

/*
** Creates alpha sorted binary tree of args
*/

void	ft_strsort(t_bi **tree, t_lsargs *args)
{
	int			i;
	struct stat	file_info;

	i = -1;
	while ((args->all_paths)[++i])
	{
		(args->d_name) ? free(args->d_name) : 0;
		args->d_name = ft_strdup((args->all_paths)[i]);
		lstat((args->all_paths)[i], &file_info);
		args->time = file_info.st_mtime;
		args->nsec = file_info.st_mtimespec.tv_nsec;
		if (S_ISDIR(file_info.st_mode))
			set_first_node(tree, args, 1);
		else
			set_first_node(tree, args, 0);
		args->time = 0;
		args->nsec = 0;
	}
}

/*
** Helps main due to norm
*/

void	main_helper(t_lsargs *args)
{
	t_bi	*tree;
	int		dir;

	dir = -1;
	tree = NULL;
	if (args->error)
		exit(1);
	if (!(args->all_paths)[0])
	{
		(args->all_paths)[0] = ".";
		listdir((args->all_paths)[args->i], 0, args);
	}
	else
	{
		ft_strsort(&tree, args);
		args->first = 0;
		while (++dir < 2)
			args_binary(tree, args, dir);
		free_binary(tree);
	}
}

int		main(int ac, char **av)
{
	t_lsargs	args;
	int			i;

	ft_bzero(&args, sizeof(args));
	args.all_paths = (char**)ft_memalloc(sizeof(char*) * ac);
	args.p = 0;
	i = 1;
	while (i < ac)
	{
		if (!args.p && av[i][0] == '-' && av[i][1] != '\0')
			parse_arg(av[i], &args);
		else
			(args.all_paths)[args.p++] = ft_strdup(av[i]);
		i++;
	}
	main_helper(&args);
	(ac > 2) ? free_array(args.all_paths) : 0;
	return (0);
}
