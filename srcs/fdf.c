/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 08:07:54 by sjuery            #+#    #+#             */
/*   Updated: 2018/10/01 18:50:57 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(char *reason)
{
	ft_putstr(reason);
	exit(1);
}

void	bresenham(t_fdf *fdf)
{
	fdf->dx = ft_abs(fdf->x2 - fdf->x1);
	fdf->sx = fdf->x1 < fdf->x2 ? 1 : -1;
	fdf->dy = ft_abs(fdf->y2 - fdf->y1);
	fdf->sy = fdf->y1 < fdf->y2 ? 1 : -1;
	fdf->err = (fdf->dx > fdf->dy ? fdf->dx : -fdf->dy) / 2;
	while (1)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, fdf->x1, fdf->y1, 0x9c0000);
		if (fdf->x1 == fdf->x2 && fdf->y1 == fdf->y2)
			break ;
		fdf->e2 = fdf->err;
		if (fdf->e2 > -fdf->dx)
		{
			fdf->err -= fdf->dy;
			fdf->x1 += fdf->sx;
		}
		if (fdf->e2 < fdf->dy)
		{
			fdf->err += fdf->dx;
			fdf->y1 += fdf->sy;
		}
	}
}

char	*convert_input(char *line)
{
	int i;

	i = 0;
	while (line[i++])
	{
		if (line[i] == '-' && ft_isdigit(line[i + 1]))
			i++;
		if (line[i] && !ft_isdigit(line[i]))
			line[i] = ' ';
	}
	return (line);
}

void	parseinput(t_fdf *fdf, int fd)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	if (!(fdf->nbr = (int **)ft_memalloc(sizeof(int *) * fdf->nbr_line)) ||
		!(fdf->nbr_split = (int *)ft_memalloc(sizeof(int) * fdf->nbr_line)))
		handle_error("Error parsing input: Check Rows\n");
	while (get_next_line(fd, &line) == 1)
	{
		i = -1;
		line = convert_input(line);
		fdf->split = ft_strsplit(line, ' ');
		fdf->nbr_split[j] = ft_strsplitcnt(fdf->split);
		if (!(fdf->nbr[j] = (int *)ft_memalloc(sizeof(int) *
					fdf->nbr_split[j])))
			handle_error("Error parsing input: Check Collums\n");
		while (fdf->split[++i])
			fdf->nbr[j][i] = ft_atoi(fdf->split[i]);
		j++;
	}
}

int		main(int argc, char **argv)
{
	t_fdf	fdf;
	int		fd;

	if (argc == 2 && (fd = open(argv[1], O_RDONLY)) != -1)
	{
		fdf.commands = 1;
		fdf.nbr_line = ft_linecount(argv[1]);
		fdf.ach_x = 1000 / 2;
		fdf.ach_y = 1000 / 4;
		fdf.scale = 20;
		parseinput(&fdf, fd);
		close(fd);
		fdf.mlx = mlx_init();
		fdf.win = mlx_new_window(fdf.mlx, 1000, 1000, "FDF");
		mlx_expose_hook(fdf.win, get_hook, &fdf);
		mlx_key_hook(fdf.win, key_hook, &fdf);
		mlx_loop(fdf.mlx);
	}
	else
		handle_error("Usage: ./fdf [Valid FdF File]\n");
	return (0);
}
