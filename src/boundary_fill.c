/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:28:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/22 23:20:35 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_element(int x, int y, t_cube *cube)
{
	return cube->map.grid[y][x];
}

static void	set_element(int x, int y, int color, t_cube *cube)
{
	cube->map.grid[y][x] = color;
}

void	rev_boundary_fill(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < cube->map.height)
	{
		x = 0;
		while (x < cube->map.width)
		{
			if (cube->map.grid[y][x] == FILL)
				cube->map.grid[y][x] = EMPTY;
			x++;
		}
		y++;
	}
}

/*
** Check if the position x,y is inside an polygon
** that has the edges set to value 1, filling it with value 3
** Adapted from: https://en.wikipedia.org/wiki/Flood_fill
** Will set '*open' variable to TRUE(1) if the position
** goes out of bounds
** open should be set to a value other than 1 before using
** this function 
*/

void	boundary_fill(int x, int y, int *open, t_cube *cube)
{
	if (x < 0 || y < 0 || x >= cube->map.width ||
			y >= cube->map.height || get_element(x, y, cube) == SPACE)
	{
		*open = TRUE;
		return;
	}
	if (get_element(x, y, cube) != WALL &&
			get_element(x, y, cube) != FILL)
	{
		set_element(x, y, FILL, cube);
		boundary_fill(x + 1, y, open, cube);
		boundary_fill(x, y + 1, open, cube);
		boundary_fill(x - 1, y, open, cube);
		boundary_fill(x, y - 1, open, cube);
	}
}
