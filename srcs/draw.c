/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 08:07:54 by sjuery            #+#    #+#             */
/*   Updated: 2018/10/01 18:51:02 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_coords(t_fdf *fdf, int x, int y, int z)
{
	if (fdf->type == 'x')
		return (fdf->ach_x - (fdf->scale * y) + (fdf->scale * x));
	else
		return (fdf->ach_y + ((fdf->scale) * x) + ((fdf->scale) * y) - (z * 2));
}

void	draw_y(t_fdf *fdf)
{
	int			i;
	int			j;

	i = 0;
	while (i < fdf->nbr_line)
	{
		j = 0;
		while (j < (fdf->nbr_split[i] - 1))
		{
			fdf->type = 'x';
			fdf->x1 = get_coords(fdf, j, i, 0);
			fdf->type = 'y';
			fdf->y1 = get_coords(fdf, j, i, fdf->nbr[i][j]);
			j++;
			fdf->type = 'x';
			fdf->x2 = get_coords(fdf, j, i, 0);
			fdf->type = 'y';
			fdf->y2 = get_coords(fdf, j, i, fdf->nbr[i][j]);
			bresenham(fdf);
		}
		i++;
	}
}

void	draw_x(t_fdf *fdf)
{
	int			i;
	int			j;

	i = 0;
	while (i < fdf->nbr_line - 1)
	{
		j = 0;
		while (j < fdf->nbr_split[i] && (fdf->nbr_split[i + 1] - j) > 0)
		{
			fdf->type = 'x';
			fdf->x1 = get_coords(fdf, j, i, 0);
			fdf->type = 'y';
			fdf->y1 = get_coords(fdf, j, i, fdf->nbr[i][j]);
			fdf->type = 'x';
			fdf->x2 = get_coords(fdf, j, i + 1, 0);
			fdf->type = 'y';
			fdf->y2 = get_coords(fdf, j, i + 1, fdf->nbr[i + 1][j]);
			bresenham(fdf);
			j++;
		}
		i++;
	}
}

int		get_hook(t_fdf *fdf)
{
	draw_y(fdf);
	draw_x(fdf);
	if (fdf->commands)
	{
		mlx_string_put(fdf->mlx,
			fdf->win, 25, 25, 0x11bdff, "FdF Commands:");
		mlx_string_put(fdf->mlx, fdf->win,
			25, 45, 0x11bdff, "'esc' -> Quit Program");
		mlx_string_put(fdf->mlx, fdf->win,
			25, 65, 0x11bdff, "'C' -> Toggle Commands Menu");
		mlx_string_put(fdf->mlx, fdf->win,
			25, 85, 0x11bdff, "'+' -> Zoom In");
		mlx_string_put(fdf->mlx, fdf->win,
			25, 105, 0x11bdff, "'-' -> Zoom Out");
		mlx_string_put(fdf->mlx, fdf->win,
			25, 125, 0x11bdff, "'Up/Down Arrows' Movement on Y Axis");
		mlx_string_put(fdf->mlx, fdf->win,
			25, 145, 0x11bdff, "'Left/Right Arrows' Movement on X Axis");
	}
	return (1);
}

int		key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		handle_error("Successfully Quit FdF\n");
	mlx_clear_window(fdf->mlx, fdf->win);
	if (keycode == 8)
		fdf->commands = !fdf->commands;
	if (keycode == 69)
		fdf->scale += 1;
	if (keycode == 78)
		fdf->scale -= 1;
	if (keycode == 126)
		fdf->ach_y -= 5;
	if (keycode == 125)
		fdf->ach_y += 5;
	if (keycode == 123)
		fdf->ach_x -= 5;
	if (keycode == 124)
		fdf->ach_x += 5;
	get_hook(fdf);
	return (0);
}
