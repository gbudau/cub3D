/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:40:20 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/28 16:43:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calc_ray_dist(t_raycast *horz, t_raycast *vert, t_map *map)
{
	if (horz->wall_hit == TRUE)
		horz->hit_dist = points_dist(map->player.x, horz->wall_hit_x,
									map->player.y, horz->wall_hit_y);
	else
		horz->hit_dist = INT_MAX;
	if (vert->wall_hit == TRUE)
		vert->hit_dist = points_dist(map->player.x, vert->wall_hit_x,
									map->player.y, vert->wall_hit_y);
	else
		vert->hit_dist = INT_MAX;
}

static void	update_ray(t_raycast *horz, t_raycast *vert, t_ray *ray)
{
	if (vert->hit_dist < horz->hit_dist)
	{
		ray->dist = vert->hit_dist;
		ray->wall_hit_x = vert->wall_hit_x;
		ray->wall_hit_y = vert->wall_hit_y;
		ray->was_hit_vert = TRUE;
		ray->was_hit_horz = FALSE;
	}
	else
	{
		ray->dist = horz->hit_dist;
		ray->wall_hit_x = horz->wall_hit_x;
		ray->wall_hit_y = horz->wall_hit_y;
		ray->was_hit_horz = TRUE;
		ray->was_hit_vert = FALSE;
	}
}

static void	cast_ray(t_map *map, t_ray *ray)
{
	t_raycast	horz;
	t_raycast	vert;

	cast_ray_horz(&horz, map, ray);
	cast_ray_vert(&vert, map, ray);
	calc_ray_dist(&horz, &vert, map);
	update_ray(&horz, &vert, ray);
}

static void	set_ray_direction(t_ray *ray)
{
	ray->is_ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray->ray_angle < PI * 0.5 ||
												ray->ray_angle > PI * 1.5;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

void		cast_rays(t_cub *cub)
{
	float	ray_angle;
	int		column;
	t_ray	*ray;

	ray_angle = cub->map.player.rotation_angle - cub->half_fov_angle;
	column = 0;
	while (column < cub->width)
	{
		ray = &cub->rays[column];
		ray->ray_angle = normalize_angle(ray_angle);
		set_ray_direction(ray);
		cast_ray(&cub->map, ray);
		ray_angle += cub->angle_step;
		column++;
	}
}
