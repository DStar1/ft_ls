/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dash_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:54:52 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/03 15:52:54 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		norm(int *i, char *c, int iset, char cset)
{
	*c = cset;
	*i = iset;
}

static int	file_type(int mode, t_lsargs *args)
{
	char	c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		norm(&(args->device), &c, 1, 'b');
	else if (S_ISCHR(mode))
		norm(&(args->device), &c, 1, 'c');
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		norm(&(args->fd), &c, 1, 'l');
	else if (S_ISSOCK(mode))
		c = 's';
	else
		c = '?';
	return (c);
}

char		*permissions(int mode, t_lsargs *args)
{
	static const char	*rwx[] = {"---", "--x", "-w-", "-wx",
		"r--", "r-x", "rw-", "rwx"};
	static char			bits[11];

	bits[0] = file_type(mode, args);
	ft_strcpy(&bits[1], rwx[(mode >> 6) & 7]);
	ft_strcpy(&bits[4], rwx[(mode >> 3) & 7]);
	ft_strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXOTH) ? 't' : 'T';
	bits[10] = '\0';
	return (bits);
}
