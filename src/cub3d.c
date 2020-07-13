/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:38:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/13 19:02:21 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


// Delete/Replace later
#include <stdio.h>
#define MAP_WIDTH 5
#define MAP_HEIGHT 5
#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 700


int		update_cube(t_cube *cube);
void	cast_ray(float ray_angle, int strip_id, t_map *map, t_ray *rays, t_cube *cube);

int grid[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,1,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1}
};

void	quit_cube(t_cube *cube, int exit_code)
{
	mlx_destroy_image(cube->mlx, cube->image.img);
	mlx_destroy_window(cube->mlx, cube->window.win);
	free(cube->rays);
	exit(exit_code);
}

int		initialize_player(t_player *player, t_window *window)
{
	player->x = window->width / 4;
	player->y = window->height / 4;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->strafe_direction = 0;
	player->rotation_angle = 0;
	player->walk_speed = WALK_SPEED;
	player->turn_speed = TURN_SPEED * (PI / 180);
	return (0);
}

int		parse_map(t_cube *cube)
{
	// TODO: Check if window.width < map.width
	// or window.height < map.height and exit with an error
	cube->window.width = WINDOW_WIDTH;
	cube->window.height = WINDOW_HEIGHT;
	cube->map.ceil_color = 0xff666666;
	cube->map.floor_color = 0xff663300;
	cube->map.width = MAP_WIDTH;
	cube->map.height = MAP_HEIGHT;
	cube->map.tile_width = cube->window.width / cube->map.width;
	cube->map.tile_height = cube->window.height / cube->map.height;
	initialize_player(&cube->map.player, &cube->window);
	return (0);
}

int		initialize_image(t_cube *cube)
{
	cube->image.img = mlx_new_image(cube->mlx, cube->window.width,
			cube->window.height);
	cube->image.addr = mlx_get_data_addr(
			cube->image.img,
			&cube->image.bits_per_pixel,
			&cube->image.size_line, 
			&cube->image.endian);
	return (0);
}

int		initialize_cube(t_cube *cube)
{
	cube->mlx = mlx_init();
	cube->window.win = mlx_new_window(cube->mlx, cube->window.width,
			cube->window.height, WINDOW_TITLE);
	cube->rays = malloc(sizeof(t_ray) * cube->window.width);
	if (cube->rays == NULL)
		quit_cube(cube, EXIT_FAILURE);
	return (0);
}

int		key_press(int	keycode, t_cube *cube)
{
	if (keycode == KEY_ESC)
	{
		quit_cube(cube, EXIT_SUCCESS);
	}
	if (keycode == KEY_W)
		cube->map.player.walk_direction = 1;
	if (keycode == KEY_S)
		cube->map.player.walk_direction = -1;
	if (keycode == KEY_D)
		cube->map.player.strafe_direction = 1;
	if (keycode == KEY_A)
		cube->map.player.strafe_direction = -1;
	if (keycode == KEY_AR_R)
		cube->map.player.turn_direction = 1;
	if (keycode == KEY_AR_L)
		cube->map.player.turn_direction = -1;
	return (0);
}

int		key_release(int keycode, t_cube *cube)
{
	if (keycode == KEY_W)
		cube->map.player.walk_direction = 0;
	if (keycode == KEY_S)
		cube->map.player.walk_direction = 0;
	if (keycode == KEY_D)
		cube->map.player.strafe_direction = 0;
	if (keycode == KEY_A)
		cube->map.player.strafe_direction = 0;
	if (keycode == KEY_AR_R)
		cube->map.player.turn_direction = 0;
	if (keycode == KEY_AR_L)
		cube->map.player.turn_direction = 0;
	return (0);
}

int		close_window(int keycode, t_cube *cube)
{
	(void)keycode;
	(void)cube;
	exit(EXIT_SUCCESS);
	return (0);
}

int		get_grid_color(int row, int col, t_cube *cube)
{
	(void)cube;
	return (grid[row][col] == 0 ? 0x00000000 : 0xffffffff);
}

void	cast_all_rays(t_cube *cube)
{
	float	ray_angle;
	float	angle_step;
	float	radian_fov;
	int		strip_id;

	radian_fov = FOV * (PI / 180);
	ray_angle = cube->map.player.rotation_angle - radian_fov / 2;
	angle_step = radian_fov / cube->window.width;
	strip_id = 0;
	while (strip_id < cube->window.width)
	{
		cast_ray(ray_angle, strip_id, &cube->map, cube->rays, cube);
		ray_angle += angle_step;
		strip_id++;
	}
}

void	draw_minimap(t_cube *cube)
{
	t_position start;
	t_position end;
	int	row;
	int	col;
	t_position scaled;

	start.y = 0;
	start.x = 0;
	while (start.y < cube->window.height)
	{
		start.x = 0;
		while (start.x < cube->window.width)
		{
			row = start.y / cube->map.tile_height;
			col = start.x / cube->map.tile_width;
			cube->map.color = get_grid_color(row, col, cube);
			scaled.x = start.x * MINIMAP_SCALE;
			scaled.y = start.y * MINIMAP_SCALE;
			end.x = scaled.x + cube->map.tile_width * MINIMAP_SCALE;
			end.y = scaled.y + cube->map.tile_height * MINIMAP_SCALE;
			draw_rectangle(cube, scaled, end);
			start.x += cube->map.tile_width;
		}
		start.y += cube->map.tile_height;
	}
}

void	render_rays(t_ray *rays, t_window *window, t_cube *cube)
{
	int			i;
	int			color;
	t_position	start;
	t_position	end;

	i = 0;
	color = 0xffff0000;
	while (i < window->width)
	{
		start.x = cube->map.player.x * MINIMAP_SCALE;
		start.y = cube->map.player.y * MINIMAP_SCALE;
		end.x = rays[i].wall_hit_x * MINIMAP_SCALE;
		end.y = rays[i].wall_hit_y * MINIMAP_SCALE;
		draw_line(cube, start, end, color);
		i++;
	}
}

void	move_player(t_player *player, t_map *map)
{
	float	move_step;
	float	new_x;
	float	new_y;
	float	strafe_angle;
	float	strafe_step;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	strafe_step = player->strafe_direction * player->walk_speed;
	strafe_angle = PI / 2 * !!player->strafe_direction;
	move_step = player->walk_direction * player->walk_speed; 
	new_x = player->x + cos(player->rotation_angle) * move_step + cos(player->rotation_angle + strafe_angle) * strafe_step;
	new_y = player->y + sin(player->rotation_angle) * move_step + sin(player->rotation_angle + strafe_angle) * strafe_step;

	if (grid[(int)(new_y / map->tile_height)][(int)(new_x / map->tile_width)] == 0)
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	draw_player(t_cube *cube, t_player *player)
{
	t_position	start;
	t_position	end;
	int			color;

	start.x = (player->x - 3 * MINIMAP_SCALE) * MINIMAP_SCALE;
	start.y = (player->y - 3 * MINIMAP_SCALE) * MINIMAP_SCALE;
	end.x = (player->x + 3 * MINIMAP_SCALE) * MINIMAP_SCALE;
	end.y = (player->y + 3 * MINIMAP_SCALE) * MINIMAP_SCALE;
	color = 0xffffffff;
	draw_rectangle(cube, start, end); 
	start.x = (player->x) * MINIMAP_SCALE;
	start.y = (player->y) * MINIMAP_SCALE;
	end.x = start.x + cos(player->rotation_angle) * 40 * MINIMAP_SCALE;
	end.y = start.y + sin(player->rotation_angle) * 40 * MINIMAP_SCALE;
	draw_line(cube, start, end, color);
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

int		map_has_wall_at(float x, float y, t_map *map, t_cube *cube)
{
	int	row;
	int	col;

	if (x < 0 || y < 0 || x > cube->window.width || y > cube->window.height)
		return (TRUE);
	row = y / map->tile_height;
	col = x / map->tile_width;
	return (grid[row][col] != 0);
}

float	distance_between_points(float x1, float x2, float y1, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(float ray_angle, int strip_id, t_map *map, t_ray *rays, t_cube *cube)
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
	int		horz_wall_content;
	float	next_horz_touch_x;
	float	next_horz_touch_y;
	float	horz_hit_distance;

	int		found_vert_wall_hit;
	float	vert_wall_hit_x;
	float	vert_wall_hit_y;
	int		vert_wall_content;
	float	next_vert_touch_x;
	float	next_vert_touch_y;
	float	vert_hit_distance;


	ray_angle = normalize_angle(ray_angle);
	is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	is_ray_facing_up = !is_ray_facing_down;
	is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	is_ray_facing_left = !is_ray_facing_right;

	// Horizontal Ray-grid intersection code
	found_horz_wall_hit = FALSE;
	horz_wall_hit_x = 0;
	horz_wall_hit_x = 0;
	horz_wall_content = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(map->player.y / map->tile_height) * map->tile_height;
	yintercept += is_ray_facing_down ? map->tile_height : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = map->player.x + (yintercept - map->player.y) / tan(ray_angle);

	// Calculate the increment xstep and ystep

	ystep = map->tile_height;
	ystep *= is_ray_facing_up ? -1 : 1;

	xstep = ystep / tan(ray_angle);
	xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

	next_horz_touch_x = xintercept;
	next_horz_touch_y = yintercept;

	// Increment xstep and ystep until we find a wall
	while (next_horz_touch_x >= 0 &&
			next_horz_touch_x <= map->tile_width * map->width &&
			next_horz_touch_y >= 0 &&
			next_horz_touch_y <= map->tile_height * map->tile_height)
	{
		x_to_check = next_horz_touch_x;
		y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 1);

		if (map_has_wall_at(x_to_check, y_to_check, map, cube))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = grid[(int)(y_to_check / map->tile_height)][(int)(x_to_check / map->tile_width)];
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
	vert_wall_hit_x = 0;
	vert_wall_content = 0;

	// Find the x-coordinate of the closest vertical grid intersection
	xintercept = floor(map->player.x / map->tile_width) * map->tile_width;
	xintercept += is_ray_facing_right ? map->tile_width : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	yintercept = map->player.y + (xintercept - map->player.x) * tan(ray_angle);

	// Calculate the increment xstep and ystep

	xstep = map->tile_width;
	xstep *= is_ray_facing_left ? -1 : 1;

	ystep = xstep * tan(ray_angle);
	ystep *= (is_ray_facing_up && ystep > 0) ? -1 : 1;
	ystep *= (is_ray_facing_down && ystep < 0) ? -1 : 1;

	next_vert_touch_x = xintercept;
	next_vert_touch_y = yintercept;

	// Increment xstep and ystep until we find a wall
	while (next_vert_touch_x >= 0 &&
			next_vert_touch_x <= map->tile_width * map->width &&
			next_vert_touch_y >= 0 &&
			next_vert_touch_y <= map->tile_height * map->height)
	{
		x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 1);
		y_to_check = next_vert_touch_y;

		if (map_has_wall_at(x_to_check, y_to_check, map, cube))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = grid[(int)(y_to_check / map->tile_height)][(int)(x_to_check / map->tile_width)];
			found_vert_wall_hit = TRUE;
			break;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	// Calculate both horizontal and vertical  distances and chose the  smallest one

	horz_hit_distance = found_horz_wall_hit
		? distance_between_points(
				map->player.x,
				horz_wall_hit_x,
				map->player.y,
				horz_wall_hit_y) : INT_MAX;

	vert_hit_distance = found_vert_wall_hit
		? distance_between_points(
				map->player.x,
				vert_wall_hit_x,
				map->player.y,
				vert_wall_hit_y) : INT_MAX;
	
	if (vert_hit_distance < horz_hit_distance)
	{
		rays[strip_id].distance = vert_hit_distance;
		rays[strip_id].wall_hit_x = vert_wall_hit_x;
		rays[strip_id].wall_hit_y = vert_wall_hit_y;
		rays[strip_id].wall_hit_content = vert_wall_content;
		rays[strip_id].was_hit_vert = TRUE;
	}
	else
	{
		rays[strip_id].distance = horz_hit_distance;
		rays[strip_id].wall_hit_x = horz_wall_hit_x;
		rays[strip_id].wall_hit_y = horz_wall_hit_y;
		rays[strip_id].wall_hit_content = horz_wall_content;
		rays[strip_id].was_hit_horz = TRUE;
	}
	rays[strip_id].ray_angle = ray_angle;
	rays[strip_id].is_ray_facing_down = is_ray_facing_down;
	rays[strip_id].is_ray_facing_up = is_ray_facing_up;
	rays[strip_id].is_ray_facing_left = is_ray_facing_left;
	rays[strip_id].is_ray_facing_right = is_ray_facing_right;
}

int		initialize_hooks(t_cube *cube)
{
	mlx_hook(cube->window.win, ClientMessage, StructureNotifyMask,
			close_window, cube);
	mlx_hook(cube->window.win, KeyPress, KeyPressMask, key_press, cube);
	mlx_hook(cube->window.win, KeyRelease, KeyReleaseMask, key_release, cube);
	return (0);
}

int		update_cube(t_cube *cube)
{
	draw_minimap(cube);
	move_player(&cube->map.player, &cube->map);
	cast_all_rays(cube);
	render_rays(cube->rays, &cube->window, cube);
	draw_player(cube, &cube->map.player);
	mlx_put_image_to_window(cube->mlx, cube->window.win,
			cube->image.img, 0, 0);
	mlx_do_sync(cube->mlx);
	return (0);
}

int		main(void)
{
	t_cube	cube;

	parse_map(&cube);
	initialize_cube(&cube);
	initialize_image(&cube);
	update_cube(&cube);
	initialize_hooks(&cube);
	mlx_loop_hook(cube.mlx, update_cube, &cube);
	mlx_loop(cube.mlx);
}
