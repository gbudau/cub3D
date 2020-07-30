/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_walls_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:08:35 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/27 21:06:57 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

int		wall_side(t_ray *ray)
{
	int	side;

	if (ray->was_hit_vert)
	{
		if (ray->is_ray_facing_right)
			side = EAST;
		else
			side = WEST;
	}
	else
	{
		if (ray->is_ray_facing_up)
			side = SOUTH;
		else
			side = NORTH;
	}
	return (side);
}

void	draw_ceiling(int x, t_wall_strip *wall, t_cub *cub)
{
	int	y;

	y = 0;
	while (y < wall->top_pix)
	{
		pixel_put(&cub->image, x, y, cub->map.ceil_color);
		y++;
	}
}

void	draw_floor(int x, t_wall_strip *wall, t_cub *cub)
{
	int	y;

	y = wall->bot_pix;
	while (y < cub->height)
	{
		pixel_put(&cub->image, x, y, cub->map.floor_color);
		y++;
	}
}
