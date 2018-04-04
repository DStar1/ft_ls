/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 01:11:40 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/04 02:02:33 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Add to binary tree helper
*/

int		set_node(t_bi **tree, char *name, t_lsargs *args, int direction)
{
	if (direction)
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

int		add_to_binary_time(t_bi *tree, char *name, t_lsargs *args)
{
	if (args->t && args->time == tree->time)
	{
		 ft_printf("%s | ag > tre | args->nsec: %d; (tree)->nsec: %d\n", name, args->nsec, (tree)->nsec);
		if (args->nsec > (tree)->nsec)
		{
			 ft_printf("args->nsec: %d; (tree)->nsec: %d | argname: %s; treename: %s | ag > tre\n", args->nsec, (tree)->nsec, name, tree->d_name);
			if (!(tree)->left)
				{printf("args->nsec: %ld; (tree)->nsec: %ld | argname: %s; treename: %s | left\n", args->nsec, (tree)->nsec, name, tree->d_name);
				if (set_node(&tree, name, args, 1))
					return (1);
				}
			(tree) = (tree)->left;
			ft_printf("Done with left\n");
		}
		else if (args->nsec < (tree)->nsec)
		{
			 ft_printf("args->nsec: %d; (tree)->nsec: %d | argname: %s; treename: %s | ag < tre\n", args->nsec, (tree)->nsec, name, tree->d_name);
			if (!(tree)->right)
				{printf("args->nsec: %ld; (tree)->nsec: %zd | argname: %s; treename: %s | right\n", args->nsec, (tree)->nsec, name, tree->d_name);
				if (set_node(&tree, name, args, 0))
					return (1);
				}
			(tree) = (tree)->right;
		}
		//else{
			return (2);
			// ft_printf("Same time\n");
		//	}
		// ft_printf("Same time\n");
	}
	// ft_printf("Not same time\n");
	return (0);
}

/*
** Sort by alphabet
*/

int		add_to_binary(t_bi *tree, char *name, t_lsargs *args, int dir)
{
	int f_time;
	ft_printf("SETTING %s\n", name);
	while (tree)
	{
		f_time = add_to_binary_time(tree, name, args);
		args->dir = dir;
		// RETURN(1, f_time == 1);
		if (f_time == 1)
			{/*ft_printf("args->t: %d; args->time: %d: tree->time: %d;\n", args->t, args->time, tree->time);*/return (1);}

		if ((ft_strcmp(name, tree->d_name) < 0 && (!args->t ||
			f_time)) || (args->t && args->time > tree->time))
		{
			if (!tree->left)
				{ft_printf("args->nsec: %d; (tree)->nsec: %d | argname: %s; treename: %s | alpha-left\n", args->nsec, (tree)->nsec, name, tree->d_name);
				if (set_node(&tree, name, args, 1))
					return (1);}
			tree = tree->left;
		}
		else if ((ft_strcmp(name, tree->d_name) >= 0 && (!args->t ||
				f_time)) || (args->t && args->time < tree->time))
		{
			if (!tree->right)
				{ft_printf("args->nsec: %d; (tree)->nsec: %d | argname: %s; treename: %s | alpha-right\n", args->nsec, (tree)->nsec, name, tree->d_name);
				if (set_node(&tree, name, args, 0))
					return (1);}
			tree = tree->right;
		}
	}
	return (0);
}

/*
** Set first node in tree
*/

void	set_first_node(t_bi **tree,
						t_lsargs *args,
						int dir)
{
	if (!(*tree))
	{
		(*tree) = (t_bi*)ft_memalloc(sizeof(t_bi));
		(*tree)->d_name = ft_strdup(args->d_name);
		(*tree)->time = (args)->time;
		(*tree)->nsec = (args)->nsec;
		(*tree)->dir = dir;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}
	else
		add_to_binary(*tree, args->d_name, (args), dir);
}
