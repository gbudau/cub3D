/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:28:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/27 19:02:02 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

static int	get_element(int x, int y, t_cub *cub)
{
	return (cub->map.grid[y][x]);
}

static void	set_element(int x, int y, int color, t_cub *cub)
{
	cub->map.grid[y][x] = color;
}

void		rev_boundary_fill(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			if (cub->map.grid[y][x] == FILL)
				cub->map.grid[y][x] = EMPTY;
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

void		boundary_fill(int x, int y, int *open, t_cub *cub)
{
	if (x < 0 || y < 0 || x >= cub->map.width ||
			y >= cub->map.height || get_element(x, y, cub) == SPACE)
	{
		*open = TRUE;
		return ;
	}
	if (get_element(x, y, cub) != WALL &&
			get_element(x, y, cub) != FILL)
	{
		set_element(x, y, FILL, cub);
		boundary_fill(x + 1, y, open, cub);
		boundary_fill(x, y + 1, open, cub);
		boundary_fill(x - 1, y, open, cub);
		boundary_fill(x, y - 1, open, cub);
	}
}
