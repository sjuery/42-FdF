/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 08:07:54 by sjuery            #+#    #+#             */
/*   Updated: 2018/10/01 18:51:21 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <unistd.h>
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	int				**nbr;
	int				nbr_line;
	int				*nbr_split;
	char			**split;
	char			type;
	int				scale;
	int				ach_x;
	int				ach_y;
	int				commands;
	int				y1;
	int				y2;
	int				x1;
	int				x2;
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e2;

}					t_fdf;

void				handle_error(char *reason);
void				bresenham(t_fdf *fdf);
int					key_hook(int keycode, t_fdf *fdf);
int					get_hook(t_fdf *fdf);
int					key_hook(int keycode, t_fdf *fdf);
int					coord_x(t_fdf *fdf, int x, int y);
void				draw_y(t_fdf *fdf);
void				draw_x(t_fdf *fdf);
#endif
