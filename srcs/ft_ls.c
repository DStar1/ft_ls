/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:34:14 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/21 01:45:42 by hasmith          ###   ########.fr       */
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
	if (!(!(*args)->a && ft_strncmp(entry->d_name, ".", 1) == 0))
	{
		if ((*args)->size_len < file_info.st_size)//count the blocks
			(*args)->size_len = file_info.st_size;
		(*args)->blocks += file_info.st_blocks;
	}
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
			listdir_loop(path, &args, entry, &tree);
		}
		args->size_len = ft_intlen(args->size_len);
		if (args->l)
			ft_printf("total %d\n", args->blocks);
		args->blocks = 0;
		if (args->r)
			print_binary_rev(tree, path, args);
		else
			print_binary(tree, path, args);
		args->size_len = 0;
		closedir(dir);
	}
	else
    	perror ("Couldn't open the directory");///////////possibly change to "ft_ls: <av[1]>"...
	if (args->c_r)
		subdir(tree, path, indent, args);
	free_binary(tree);
}

/*
** Parsing args
*/

// void parse_args(t_ls *ls, int ac, char **av)
// {
// 	while ()
// 	{
		
// 	}
// }


int main(int ac, char **av)//test with /dev
{
	char *path;
	t_ls ls;
	t_lsargs args;

	ft_bzero(&args, sizeof(args));
	path = NULL;
	int i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-R"))
			args.c_r = 1;
		else if (!ft_strcmp(av[i], "-l"))
			args.l = 1;
		else if (!ft_strcmp(av[i], "-a"))
			args.a = 1;
		else if (!ft_strcmp(av[i], "-t"))
			args.t = 1;
		else if (!ft_strcmp(av[i], "-r"))
			args.r = 1;
		else if (i == ac - 1)
			path = ft_strdup(av[ac - 1]);
		else
			ft_printf("Invalid Input\n");
		i++;
	}
	if (!path)
		path = ".";
	listdir(path, 0, &args); //first arg is the path
	// ft_printf("%s\n", path);
	// while (1)
	// 		;
	return (0);
}

