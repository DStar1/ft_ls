/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/12 13:32:54 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"

typedef struct		s_ls
{
	int				ret;
	int				i;
	int				fd;
	char			*fmt;
	// va_list			ap;
}					t_ls;

// typedef struct		s_flags
// {
// 	int				i;
// }					t_flags;

typedef struct		s_bi
{
    // ino_t          d_ino;       /* inode number */
    // off_t          d_off;       /* offset to the next dirent */
    // unsigned short d_reclen;    /* length of this record */
    // unsigned char  d_type;      /* type of file; not supported
    //                                by all file system types */
	int				dir;
    char           *d_name;//[256]; /* filename */
	int				d_type;
	struct s_bi	*left;
	struct s_bi	*right;
}					t_bi;

int ft_ls(char *fmt, ...);
void	subdir(t_bi *tree, char *path, int indent);
void listdir(char *path, int indent);

#endif
