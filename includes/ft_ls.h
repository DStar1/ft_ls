/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2018/03/05 23:33:53 by hasmith          ###   ########.fr       */
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
	va_list			ap;
}					t_ls;

// typedef struct		s_flags
// {
// 	int				i;
// }					t_flags;

// typedef struct		s_master
// {
// 	int				i;
// 	int				j;
// 	void			*somthing;
// 	struct s_master	*next;
// }					t_master;

int ft_ls(char *fmt, ...);

#endif
