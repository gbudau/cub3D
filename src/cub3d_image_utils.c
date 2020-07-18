/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_image_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:06:18 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/16 22:41:51 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int			pixel_get(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

static void	line_increase_position(int *error, int *pos, int step, int delta)
{
	*error += delta;
	*pos += step;
}

/*
** Bresenheim line draw algorithm
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*/

void		draw_line(t_cube *cube, t_point start, t_point end, int color)
{
	t_line_var line;

	line.dx = ft_abs(end.x - start.x);
	line.sx = start.x < end.x ? 1 : -1;
	line.dy = -ft_abs(end.y - start.y);
	line.sy = start.y < end.y ? 1 : -1;
	line.error = line.dx + line.dy;
	while (1)
	{
		if ((start.x >= 0 && start.x < cube->width) &&
				(start.y >= 0 && start.y < cube->height))
			pixel_put(&cube->image, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		line.error2 = 2 * line.error;
		if (line.error2 >= line.dy)
			line_increase_position(&line.error, &start.x, line.sx, line.dy);
		if (line.error2 <= line.dx)
			line_increase_position(&line.error, &start.y, line.sy, line.dx);
	}
}

void		draw_rectangle(t_cube *cube, t_point start, t_point end, int color)
{
	int tmp;

	tmp = start.x;
	while (start.y <= end.y && start.y < cube->height)
	{
		start.x = tmp;
		while (start.x <= end.x && start.x < cube->width)
		{
			pixel_put(&cube->image, start.x, start.y, color);
			start.x++;
		}
		start.y++;
	}
}
