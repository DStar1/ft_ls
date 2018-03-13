/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:34:14 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/12 19:21:17 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

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
** print tree in alpha order
*/

void	print_binary(t_bi *tree)
{
	if (tree == NULL)
		return ;
	print_binary(tree->left);
	ft_printf("%s\n", tree->d_name);
	print_binary(tree->right);
}

/*
** Sort by alphabet
*/

int	add_to_binary(t_bi *tree, char *name, int d_type, int dir)
{
	int i;

	i = 0;
	while (tree)
	{
		if (ft_strcmp(name, tree->d_name) < 0)
		{
			if (!tree->left)
			{
				tree->left = (t_bi*)ft_memalloc(sizeof(t_bi));
				tree->left->d_name = ft_strdup(name);
				tree->left->d_type = d_type;
				tree->left->dir = dir;
				tree->left->left = NULL;
				tree->left->right = NULL;
				return (1);
			}
			tree = tree->left;
		}
		else
		{
			if (!tree->right)
			{
				tree->right = (t_bi*)ft_memalloc(sizeof(t_bi));
				tree->right->d_name = ft_strdup(name);
				tree->right->d_type = d_type;
				tree->right->dir = dir;
				tree->right->left = NULL;
				tree->right->right = NULL;
				return (1);
			}
			tree = tree->right;
		}
	}
	return (0);
}

/*
** parse args
** read args
*/

void listdir(char *path, int indent)
{
	DIR *dir;
	struct dirent *entry;
	t_bi *tree;
	char *path1;
	struct stat file_info;////lstat
	// path = ft_strdup("./srcs/test_dir");
	// char *path1;
	// char path1[1024];

	ft_bzero(&tree, sizeof(&tree));
	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)) != NULL)
		{

			// lstat(entry->d_name, &file_info);
			//to get the right path
			path1 = ft_strjoin(path, "/");
        	path1 = ft_strjoin_clr_1st(path1, entry->d_name);

			// printf("PATH1: %s\n", path1);
			lstat(path1, &file_info); //////////////
			if (S_ISDIR(file_info.st_mode))//directory
			{
				// ft_printf("YOOOOOOOOOOOOOOOOOOOO %s\n", entry->d_name);
				// char path1[1024];
				if (ft_strncmp(entry->d_name, ".", 1) == 0)// || ft_strcmp(entry->d_name, "..") == 0)//hides the . directories (add -a flag check here)
					continue;
				if (!tree)
				{
					tree = (t_bi*)ft_memalloc(sizeof(t_bi));
					tree->d_name = ft_strdup(entry->d_name);
					tree->d_type = entry->d_type;
					tree->dir = 1;
					tree->left = NULL;
					tree->right = NULL;
				}
				else
				{
					add_to_binary(tree, entry->d_name, entry->d_type, 1);
					// ft_printf("%s\n", entry->d_name);
				}
				// snprintf(path1, sizeof(path1), "%s/%s", path1, entry->d_name);
				// printf("%*s[%s]\n", indent, "", entry->d_name);
				// listdir(path1, indent + 2);
			}
			else// if (S_ISREG(file_info.st_mode))//reg file
			{
				if (!tree)
				{
					tree = (t_bi*)ft_memalloc(sizeof(t_bi));
					tree->d_name = ft_strdup(entry->d_name);
					tree->d_type = entry->d_type;
					tree->left = NULL;
					tree->right = NULL;
				}
				else
				{
					add_to_binary(tree, entry->d_name, entry->d_type, 0);
					// ft_printf("%s\n", entry->d_name);
				}
			}
		}
		print_binary(tree);
		// free_binary(tree);
		// chdir("..");
		closedir(dir);
	}
	else
    	perror ("Couldn't open the directory");///////////possibly change to "ft_ls: <av[1]>"...
	
///////////if -R	

	subdir(tree, path, indent);//goes throught binary tree and finds all directories and does listdir for each
	// listdir(path1, indent);//////////////////
	free_binary(tree);






	
	// if ((dir = opendir(path)))
	// {
	// 	while ((entry = readdir(dir)) != NULL)
	// 	{
	// 		// ft_printf("YOOOOOOOOOOOOOOOOOOOO %c %s\n", entry->d_type, entry->d_name);
	// 		lstat(entry->d_name, &file_info); 
	// 		if (S_ISDIR(file_info.st_mode))//directory
	// 		{
	// 			// printf("%s\n", entry->d_name);
				
	// 			if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
	// 				continue;
	// 			snprintf(path1, sizeof(path1), "%s/%s", path, entry->d_name);//make new path
	// 			printf("%*s[%s]: Path: %s\n", indent, "", entry->d_name, path1);
	// 			// listdir(path1, indent + 2);
	// 		}
	// 		// else {
    //         // printf("%*s- %s\n", indent, "", entry->d_name);
    //     	// }
	// 	}
	// 	closedir(dir);
	// }
	// else
    // 	perror ("Couldn't open the directory");///////////possibly change to "ft_ls: <av[1]>"...
}

void listdir1(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
	struct stat file_info;////lstat

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
		lstat(entry->d_name, &file_info); 
        if (file_info.st_mode&S_IFDIR) {
            char path[1024];
            if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir1(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
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
	
	path = ".";
	if (ac > 1)
	{
		path = av[1];
		// parse_args(&ls, ac + 1, av);
	}
	// RecDir(path, 1);
	listdir(path, 0); //first arg is the path
	// while (1)
		// 	;
	return (0);
}

