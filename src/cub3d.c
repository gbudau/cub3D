/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:38:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/26 18:37:44 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	cast_ray(float ray_angle, int column, t_map *map, t_ray *rays)
{
	int 	is_ray_facing_down;
	int 	is_ray_facing_up;
	int 	is_ray_facing_right;
	int 	is_ray_facing_left;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	y_to_check;
	float	x_to_check;

	int		found_horz_wall_hit;
	float	horz_wall_hit_x;
	float	horz_wall_hit_y;
	float	next_horz_touch_x;
	float	next_horz_touch_y;
	float	horz_hit_dist;

	int		found_vert_wall_hit;
	float	vert_wall_hit_x;
	float	vert_wall_hit_y;
	float	next_vert_touch_x;
	float	next_vert_touch_y;
	float	vert_hit_dist;

	ray_angle = normalize_angle(ray_angle);
	is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	is_ray_facing_up = !is_ray_facing_down;
	is_ray_facing_right = ray_angle < PI * 0.5 || ray_angle > PI * 1.5;
	is_ray_facing_left = !is_ray_facing_right;

	// Horizontal Ray-grid intersection code
	found_horz_wall_hit = FALSE;
	horz_wall_hit_x = 0;
	horz_wall_hit_y = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = (int)(map->player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += is_ray_facing_down ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = map->player.x + (yintercept - map->player.y) / tan(ray_angle);

	// Calculate the increment xstep and ystep

	ystep = TILE_SIZE;
	ystep *= is_ray_facing_up ? -1 : 1;

	xstep = ystep / tan(ray_angle);
	xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

	next_horz_touch_x = xintercept;
	next_horz_touch_y = yintercept;

	// Increment xstep and ystep until we find a wall
	while (next_horz_touch_x >= 0 &&
			next_horz_touch_x < TILE_SIZE * map->width &&
			next_horz_touch_y >= 0 &&
			next_horz_touch_y < TILE_SIZE * map->height)
	{
		x_to_check = next_horz_touch_x;
		y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 1);

		if (is_wall(x_to_check, y_to_check, map))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			found_horz_wall_hit = TRUE;
			break;
		}
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
	}

	// Vertical Ray-grid intersection code
	found_vert_wall_hit = FALSE;
	vert_wall_hit_x = 0;
	vert_wall_hit_y = 0;

	// Find the x-coordinate of the closest vertical grid intersection
	xintercept = (int)(map->player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += is_ray_facing_right ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	yintercept = map->player.y + (xintercept - map->player.x) * tan(ray_angle);

	// Calculate the increment xstep and ystep

	xstep = TILE_SIZE;
	xstep *= is_ray_facing_left ? -1 : 1;

	ystep = xstep * tan(ray_angle);
	ystep *= (is_ray_facing_up && ystep > 0) ? -1 : 1;
	ystep *= (is_ray_facing_down && ystep < 0) ? -1 : 1;

	next_vert_touch_x = xintercept;
	next_vert_touch_y = yintercept;

	// Increment xstep and ystep until we find a wall
	while (next_vert_touch_x >= 0 &&
			next_vert_touch_x < TILE_SIZE * map->width &&
			next_vert_touch_y >= 0 &&
			next_vert_touch_y < TILE_SIZE * map->height)
	{
		x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 1);
		y_to_check = next_vert_touch_y;

		if (is_wall(x_to_check, y_to_check, map))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			found_vert_wall_hit = TRUE;
			break;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	// Calculate both horizontal and vertical  dists and choose the  smallest one

	horz_hit_dist = found_horz_wall_hit
		? points_dist(
				map->player.x,
				horz_wall_hit_x,
				map->player.y,
				horz_wall_hit_y) : INT_MAX;

	vert_hit_dist = found_vert_wall_hit
		? points_dist(
				map->player.x,
				vert_wall_hit_x,
				map->player.y,
				vert_wall_hit_y) : INT_MAX;
	
	if (vert_hit_dist < horz_hit_dist)
	{
		rays[column].dist = vert_hit_dist;
		rays[column].wall_hit_x = vert_wall_hit_x;
		rays[column].wall_hit_y = vert_wall_hit_y;
		rays[column].was_hit_vert = TRUE;
		rays[column].was_hit_horz = FALSE;
	}
	else
	{
		rays[column].dist = horz_hit_dist;
		rays[column].wall_hit_x = horz_wall_hit_x;
		rays[column].wall_hit_y = horz_wall_hit_y;
		rays[column].was_hit_horz = TRUE;
		rays[column].was_hit_vert = FALSE;
	}
	rays[column].ray_angle = ray_angle;
	rays[column].is_ray_facing_down = is_ray_facing_down;
	rays[column].is_ray_facing_up = is_ray_facing_up;
	rays[column].is_ray_facing_left = is_ray_facing_left;
	rays[column].is_ray_facing_right = is_ray_facing_right;
}

void	minimap(t_cub *cub)
{
		draw_minimap(cub);
		draw_rays_minimap(cub->rays, cub);
		draw_player_minimap(cub, &cub->map.player);
		draw_sprites_minimap(cub);
}

void	render(t_cub *cub)
{
	project_walls(cub);
	draw_sprites(cub);
	if (cub->minimap)
		minimap(cub);
}

int		update(t_cub *cub)
{
	move_player(&cub->map.player, cub);
	cast_rays(cub);
	render(cub);
	mlx_put_image_to_window(cub->mlx, cub->win,
			cub->image.img, 0, 0);
	mlx_do_sync(cub->mlx);
	return (0);
}

void	update_savebmp(t_cub *cub)
{
	cast_rays(cub);
	project_walls(cub);
	draw_sprites(cub);
	save_bitmap(cub);
	quit_cub(cub, EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(cub));
	if (check_args(argc, argv, &cub))
		return (EXIT_FAILURE);
	parse_cub(argv[1], &cub);
	initialize(&cub);
	if (cub.savebmp == 0)
		set_hooks(&cub);
	else
		update_savebmp(&cub);
	mlx_loop_hook(cub.mlx, update, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
