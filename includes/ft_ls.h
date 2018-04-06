/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/04/05 23:41:57 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
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
	char			link_path[1024];
	char			suffix;
	// struct passwd	user;
	// struct group	group;
	char			*pw_name;
	char			*gr_name;
	char			*ctime;
	int				links;
	int				size;
	char			*year_month;
	char			*month_time;
	char			*path;
	int				blocks;
	char			*perms;
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
	char			*d_name;
	int				one;
}					t_lsargs;

typedef struct		s_bi
{
	int				dir;
	char			*d_name;
	char			*path;
	int				d_type;
	long			time;
	long			sec;
	long			nsec;
	struct s_bi		*left;
	struct s_bi		*right;
}					t_bi;

int					ft_ls(char *fmt, ...);
void				subdir(t_bi *tree, char *path, int indent, t_lsargs *args);
void				listdir(char *path, int indent, t_lsargs *args);
char				*permissions(int mode, t_lsargs *args);
char				*construct_path(char *path, char *name);
void				print_binary_rev(t_bi *tree, char *path, t_lsargs *args);
void				free_binary(t_bi *tree);
void				suffix(char *dir, t_lsargs *data);
void				set_first_node(t_bi **tree,
									t_lsargs *args,
									int dir);
void				print_binary(t_bi *tree,
								char *path,
								t_lsargs *args,
								int one);

#endif
