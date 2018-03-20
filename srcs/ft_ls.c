/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:34:14 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/19 23:28:55 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
//////////////////////////////////////////////////////////sometimes it segfaults on -R!!!!!!!!!!!!!!!!! the first time I go into recursive function/// path is wrong in recursion!!!!!!

/*
** print tree in alpha order
*/

void	free_binary(t_bi *tree)
{
	if (tree == NULL)
		return ;
	free_binary(tree->left);
	free_binary(tree->right);
	free(tree);
}

/*
** set data for dash l
*/

int	setdata(t_bi *tree, char *path, t_lsargs *args)
{
	struct stat file_info;////lstat
	char *lstatpath;

	// if (args->path)
	// 	free(args->path);
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
	// args->blocks += file_info.st_blocks;
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

/*
** Add to binary tree helper
*/

int	set_node(t_bi **tree, char *name, t_lsargs *args, int direction)
{
	if (direction)//go left
	{
		(*tree)->left = (t_bi*)ft_memalloc(sizeof(t_bi));
		(*tree)->left->d_name = ft_strdup(name);
		(*tree)->left->time = args->time;
		(*tree)->left->nsec = args->nsec;
		(*tree)->left->dir = args->dir;
		(*tree)->left->left = NULL;
		(*tree)->left->right = NULL;
		return (1);
	}
	else
	{
		(*tree)->right = (t_bi*)ft_memalloc(sizeof(t_bi));
		(*tree)->right->d_name = ft_strdup(name);
		(*tree)->right->time = args->time;
		(*tree)->right->nsec = args->nsec;
		(*tree)->right->dir = args->dir;
		(*tree)->right->left = NULL;
		(*tree)->right->right = NULL;
		return (1);	
	}
	return (0);
}

int	add_to_binary_time(t_bi *tree, char *name, t_lsargs *args, int dir)
{
	return (0);
}

/*
** Sort by alphabet
*/

int	add_to_binary(t_bi *tree, char *name, t_lsargs *args, int dir)
{
	int f_time;

	while (tree)
	{
		f_time = 0;
		args->dir = dir;
		if (args->t && args->time == tree->time)
		{
			if (args->nsec > (tree)->nsec)
			{
				if (!(tree)->left)
					if (set_node(&tree, name, args, 1))
						return (1);
				(tree) = (tree)->left;
			}
			else if (args->nsec < (tree)->nsec)
			{
				if (!(tree)->right)
					if (set_node(&tree, name, args, 0))
						return (1);
				(tree) = (tree)->right;
			}
			else
				f_time = 1;
		}
		if ((ft_strcmp(name, tree->d_name) < 0 && (!args->t || f_time)) || (args->t && args->time > tree->time))
		{
			if (!tree->left)
				if (set_node(&tree, name, args, 1))
					return (1);
			tree = tree->left;
		}
		else if ((ft_strcmp(name, tree->d_name) >= 0 && (!args->t || f_time)) || (args->t && args->time < tree->time))
		{
			if (!tree->right)
				if (set_node(&tree, name, args, 0))
					return (1);
			tree = tree->right;
		}
	}
	return (0);
}

/*
** parse args
** read args
*/

void listdir(char *path, int indent, t_lsargs *args)
{
	DIR *dir;
	struct dirent *entry;
	t_bi *tree;
	char *path2;
	struct stat file_info;////lstat

	ft_bzero(&tree, sizeof(&tree));
	path2 = NULL;
	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)) != NULL)
		{
			//to get the right path
			// args->path = ft_strjoin(*path, "/");
        	// args->path = ft_strjoin_clr_1st(args->path, entry->d_name);
			if (path2)
				free(path2);
			// ft_printf("Passing path: %s to construct\n", path);
			path2 = construct_path(path, entry->d_name);
			// ft_printf("NEWPATH in listdir: %s | OLDPATH in listdir: %s\n", path2, path);

			// printf("args->PATH: %s\n", args->path);
			lstat(path2, &file_info); //////////////
			args->time = file_info.st_mtime;////////////free?????
			args->nsec = file_info.st_mtimespec.tv_nsec;
			if (!(!args->a && ft_strncmp(entry->d_name, ".", 1) == 0))
			{
				if (args->size_len < file_info.st_size)//count the blocks
					args->size_len = file_info.st_size;
				args->blocks += file_info.st_blocks;
			}
			if (S_ISDIR(file_info.st_mode))//directory
			{
				if (!args->a && ft_strncmp(entry->d_name, ".", 1) == 0)// || ft_strcmp(entry->d_name, "..") == 0)//hides the . directories (add -a flag check here)
					continue;
				if (!tree)
				{
					tree = (t_bi*)ft_memalloc(sizeof(t_bi));
					tree->d_name = ft_strdup(entry->d_name);
					tree->time = args->time;
					tree->nsec = args->nsec;
					tree->dir = 1;
					tree->left = NULL;
					tree->right = NULL;
				}
				else
					add_to_binary(tree, entry->d_name, args, 1);
			}
			else// if (S_ISREG(file_info.st_mode))//reg file
			{
				if (!tree)
				{
					tree = (t_bi*)ft_memalloc(sizeof(t_bi));
					tree->d_name = ft_strdup(entry->d_name);
					tree->time = args->time;
					tree->nsec = args->nsec;
					tree->left = NULL;
					tree->right = NULL;
				}
				else
				{
					add_to_binary(tree, entry->d_name, args, 0);
					// ft_printf("%s\n", entry->d_name);
				}
			}
		}
		args->size_len = ft_intlen(args->size_len);
		if (args->l)
			ft_printf("total %d\n", args->blocks);
		args->blocks = 0;
		if (args->r)
			print_binary_rev(tree, path, args);/////////////////////////
		else
			print_binary(tree, path, args);
		args->size_len = 0;
		closedir(dir);
	}
	else
    	perror ("Couldn't open the directory");///////////possibly change to "ft_ls: <av[1]>"...
	if (args->c_r)///////////if -R
		subdir(tree, path, indent, args);//goes throught binary tree and finds all directories and does listdir for each
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
	if (ac > 1)
	{
		path = ft_strdup(av[1]);
		// parse_args(&ls, ac + 1, av);
	}
	else
		path = ".";
	int i = 2;
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
		i++;
	}
	// ft_printf("Path: %s\n", construct_path(".", "hello"));
	listdir(path, 0, &args); //first arg is the path
	
	// free(path);
	// while (1)
	// 		;
	return (0);
}

