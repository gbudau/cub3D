/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_vertical.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:07:27 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/28 17:30:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	find_vert_wall(t_raycast *vert, t_map *map, t_ray *ray)
{
	while (vert->next_touch_x >= 0 &&
			vert->next_touch_x < TILE_SIZE * map->width &&
			vert->next_touch_y >= 0 &&
			vert->next_touch_y < TILE_SIZE * map->height)
	{
		vert->x_to_check = vert->next_touch_x +
											(ray->is_ray_facing_left ? -1 : 1);
		vert->y_to_check = vert->next_touch_y;
		if (is_wall(vert->x_to_check, vert->y_to_check, map))
		{
			vert->wall_hit_x = vert->next_touch_x;
			vert->wall_hit_y = vert->next_touch_y;
			vert->wall_hit = TRUE;
			break ;
		}
		else
		{
			vert->next_touch_x += vert->xstep;
			vert->next_touch_y += vert->ystep;
		}
	}
}

void		cast_ray_vert(t_raycast *vert, t_map *map, t_ray *ray)
{
	vert->wall_hit = FALSE;
	vert->wall_hit_x = 0;
	vert->wall_hit_y = 0;
	vert->xintercept = (int)(map->player.x / TILE_SIZE) * TILE_SIZE;
	vert->xintercept += ray->is_ray_facing_right ? TILE_SIZE : 0;
	vert->yintercept = map->player.y + (vert->xintercept - map->player.x) *
														tan(ray->ray_angle);
	vert->xstep = TILE_SIZE;
	vert->xstep *= ray->is_ray_facing_left ? -1 : 1;
	vert->ystep = vert->xstep * tan(ray->ray_angle);
	vert->ystep *= (ray->is_ray_facing_up && vert->ystep > 0) ? -1 : 1;
	vert->ystep *= (ray->is_ray_facing_down && vert->ystep < 0) ? -1 : 1;
	vert->next_touch_x = vert->xintercept;
	vert->next_touch_y = vert->yintercept;
	find_vert_wall(vert, map, ray);
}
