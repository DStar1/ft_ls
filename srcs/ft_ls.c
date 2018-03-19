/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:34:14 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/18 22:37:16 by hasmith          ###   ########.fr       */
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
	free(tree);
}

/*
** print tree in reverse alpha order
*/

void	print_binary_rev(t_bi *tree, char **path)
{
	if (tree == NULL)
		return ;
	print_binary_rev(tree->right, path);
	ft_printf("%s\n", tree->d_name);
	print_binary_rev(tree->left, path);
}

/*
** set data for dash l
*/

int	setdata(t_bi *tree, char **path, t_lsargs *args)
{
	struct stat file_info;////lstat
	// char *path2;

	args->path = ft_strjoin(*path, "/");
	args->path = ft_strjoin_clr_1st(args->path, tree->d_name);
	lstat(args->path, &file_info);
	args->permissions = permissions(file_info.st_mode, args);
	args->user = *getpwuid(file_info.st_uid);
	args->group = *getgrgid(file_info.st_gid);
	args->ctime = ctime(&tree->time);
	args->month_time = ft_strsub(args->ctime, 4, 12);
	args->links = file_info.st_nlink;
	args->size = file_info.st_size;
	return (0);
}

/*
** print tree in alpha order
*/

void	print_binary(t_bi *tree, char **path, t_lsargs *args)
{
	if (tree == NULL)
		return ;
	print_binary(tree->left, path, args);
	if (args->l)
	{
		setdata(tree, path, args);
		ft_printf("%-10s  %d %-8.8s %-10s  %6d %s %-14s\n", args->permissions, args->links, args->user.pw_name, args->group.gr_name, args->size, args->month_time, tree->d_name);
		free(args->path);
		// free(args->permissions);
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

/*
** Sort by alphabet
*/

int	add_to_binary(t_bi *tree, char *name, t_lsargs *args, int dir)
{
	int i;
	int f_time;

	i = 0;
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

void listdir(char **path, int indent, t_lsargs *args)
{
	DIR *dir;
	struct dirent *entry;
	t_bi *tree;
	// char *args->path;
	struct stat file_info;////lstat

	ft_bzero(&tree, sizeof(&tree));
	if ((dir = opendir(*path)))
	{
		while ((entry = readdir(dir)) != NULL)
		{

			// lstat(entry->d_name, &file_info);
			//to get the right path
			args->path = ft_strjoin(*path, "/");
        	args->path = ft_strjoin_clr_1st(args->path, entry->d_name);

			// printf("args->PATH: %s\n", args->path);
			lstat(args->path, &file_info); //////////////
			args->time = file_info.st_mtime;////////////free?????
			
			args->nsec = file_info.st_mtimespec.tv_nsec;
			// args->sec = file_info.st_mtimespec.tv_sec;
			// printf("%d\n", args->time);
			if (S_ISDIR(file_info.st_mode))//directory
			{
				// ft_printf("YOOOOOOOOOOOOOOOOOOOO %s\n", entry->d_name);
				// char args->path[1024];
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
				{
					add_to_binary(tree, entry->d_name, args, 1);
					// ft_printf("%s\n", entry->d_name);
				}
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
		if (args->r)
			print_binary_rev(tree, path);/////////////////////////
		else
			print_binary(tree, path, args);
		closedir(dir);
	}
	else
    	perror ("Couldn't open the directory");///////////possibly change to "ft_ls: <av[1]>"...
	
///////////if -R	
	if (args->c_r)
		subdir(tree, path, indent, args);//goes throught binary tree and finds all directories and does listdir for each
	// listdir(args->path, indent);//////////////////
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
		path = av[1];
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
	listdir(&path, 0, &args); //first arg is the path
	// free(path);
	// while (1)
	// 		;
	return (0);
}

