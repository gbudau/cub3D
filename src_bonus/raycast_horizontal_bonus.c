/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_horizontal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:06:01 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/28 17:24:09 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

/*
** Increment xstep and ystep until we find a wall
*/

static void	find_horz_wall(t_raycast *horz, t_map *map, t_ray *ray)
{
	while (horz->next_touch_x >= 0 &&
			horz->next_touch_x < TILE_SIZE * map->width &&
			horz->next_touch_y >= 0 &&
			horz->next_touch_y < TILE_SIZE * map->height)
	{
		horz->x_to_check = horz->next_touch_x;
		horz->y_to_check = horz->next_touch_y +
											(ray->is_ray_facing_up ? -1 : 1);
		if (is_wall(horz->x_to_check, horz->y_to_check, map))
		{
			horz->wall_hit_x = horz->next_touch_x;
			horz->wall_hit_y = horz->next_touch_y;
			horz->wall_hit = TRUE;
			break ;
		}
		else
		{
			horz->next_touch_x += horz->xstep;
			horz->next_touch_y += horz->ystep;
		}
	}
}

void		cast_ray_horz(t_raycast *horz, t_map *map, t_ray *ray)
{
	horz->wall_hit = FALSE;
	horz->wall_hit_x = 0;
	horz->wall_hit_y = 0;
	horz->yintercept = (int)(map->player.y / TILE_SIZE) * TILE_SIZE;
	horz->yintercept += ray->is_ray_facing_down ? TILE_SIZE : 0;
	horz->xintercept = map->player.x + (horz->yintercept - map->player.y) /
															tan(ray->ray_angle);
	horz->ystep = TILE_SIZE;
	horz->ystep *= ray->is_ray_facing_up ? -1 : 1;
	horz->xstep = horz->ystep / tan(ray->ray_angle);
	horz->xstep *= (ray->is_ray_facing_left && horz->xstep > 0) ? -1 : 1;
	horz->xstep *= (ray->is_ray_facing_right && horz->xstep < 0) ? -1 : 1;
	horz->next_touch_x = horz->xintercept;
	horz->next_touch_y = horz->yintercept;
	find_horz_wall(horz, map, ray);
}
