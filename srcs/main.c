/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 21:44:20 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/02 18:28:19 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

void	ft_strswap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	ft_strsort(t_lsargs *args)
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

/*
** Add error message?
*/

void	main_helper(t_lsargs *args)
{
	if (args->error)
		exit(1);
	if (!(args->all_paths)[0])
	{
		(args->all_paths)[0] = ".";
		listdir((args->all_paths)[args->i], 0, args);
	}
	else
	{
		ft_strsort(args);
		args->i = -1;
		while ((args->all_paths)[++args->i])
		{
			args->first = 0;
			listdir((args->all_paths)[args->i], 0, args);
			if (!args->error && args->p && args->i != args->p - 1)
				ft_putchar('\n');
			args->error = 0;
		}
	}
}

int		main(int ac, char **av)
{
	char		**path;
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
	return (0);
}