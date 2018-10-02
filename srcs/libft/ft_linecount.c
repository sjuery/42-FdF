/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linecount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 18:34:35 by sjuery            #+#    #+#             */
/*   Updated: 2018/10/01 18:34:37 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_linecount(char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
		line_count++;
	close(fd);
	return (line_count);
}
