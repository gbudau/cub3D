/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:16:09 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/27 15:43:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

float	normalize_angle(float angle)
{
	angle = remainderf(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float	points_dist(float x1, float x2, float y1, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int		grid_color(int row, int col, t_cub *cub)
{
	if (cub->map.grid[row][col] == EMPTY)
		return (EMPTY_COL);
	else if (cub->map.grid[row][col] == SPACE)
		return (SPACE_COL);
	return (WALL_COL);
}

int		is_wall(int x, int y, t_map *map)
{
	int	row;
	int	col;

	if (x < 0 || x >= TILE_SIZE * map->width ||
			y < 0 || y >= TILE_SIZE * map->height)
		return (TRUE);
	row = y / TILE_SIZE;
	col = x / TILE_SIZE;
	return (map->grid[row][col] == 1);
}
