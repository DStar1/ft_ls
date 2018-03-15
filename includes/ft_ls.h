/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/15 16:19:55 by hasmith          ###   ########.fr       */
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

typedef struct		s_lsargs
{
	int				l;
	int				c_r;
	int				r;
	int				t;
	int				a;
	char			path[255];/////?
	int				time;
	int				right;
	int				left;
	int				dir;
	// int				time2;
}					t_lsargs;

typedef struct		s_bi
{
    // ino_t          d_ino;       /* inode number */
    // off_t          d_off;       /* offset to the next dirent */
    // unsigned short d_reclen;    /* length of this record */
    // unsigned char  d_type;      /* type of file; not supported
    //                                by all file system types */
	int				dir;
    char			*d_name;//[256]; /* filename */
	int				d_type;
	time_t			time;
	struct s_bi	*left;
	struct s_bi	*right;
	// union			u_dir
	// {
	// 	struct		s_mem
	// 	{
	// 		struct s_bi *left;
	// 		struct s_bi *right;
	// 	};
	// 	struct s_bi *direction[2];
	// };
}					t_bi;

int		ft_ls(char *fmt, ...);
void	subdir(t_bi *tree, char *path, int indent, t_lsargs *args);
void	listdir(char *path, int indent, t_lsargs *args);

#endif
