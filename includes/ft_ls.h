/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/21 23:54:02 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>

# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

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
	int				error;
	char			**all_paths;
	int				p;
	int				i;
	int				first;
	int				device;
	int				fd;
	char			*link_path;
	// char			path[255];/////?
	struct passwd	user;
	struct group	group;
	char			*ctime;
	int				links;
	int				size;
	char			*year_month;
	char			*month_time;
	char			*path;
	int				blocks;
	char			*permissions;
	long			time;
	long			sec;
	long			nsec;
	int				right;
	int				left;
	int				dir;
	int				size_len;
	int				size_links;
	int				user_len;
	int				group_len;
	int				minor_len;
	int				major_len;
	unsigned int	minor;
	unsigned int	major;
	int				maj_min;
	int				maj_min_len;
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
	char			*path;
	int				d_type;
	long			time;
	long			sec;
	long			nsec;
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
char	*permissions(int mode, t_lsargs *args);
char	*construct_path(char *path, char *name);
void	print_binary(t_bi *tree, char *path, t_lsargs *args);
void	print_binary_rev(t_bi *tree, char *path, t_lsargs *args);
void	free_binary(t_bi *tree);
void	set_first_node(t_bi **tree, struct dirent *entry, t_lsargs *args, int dir);

#endif
