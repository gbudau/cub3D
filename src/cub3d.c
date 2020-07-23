/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:38:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/23 19:49:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Delete/replace later
#include <stdio.h>

int		update_cube(t_cube *cube);
void	cast_ray(float ray_angle, int column, t_map *map, t_ray *rays);
float	normalize_angle(float angle);

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	quit_cube(t_cube *cube, int exit_code)
{
	int	i;

	free(cube->rays);
	free(cube->sprites);
	free_int_matrix(cube->map.grid, cube->map.height);
	i = 0;
	while (i < TEXTURES)
	{
		free(cube->map.paths[i]);
		if (cube->texture[i].image.img)
			mlx_destroy_image(cube->mlx, cube->texture[i].image.img);
		i++;
	}
	if (cube->mlx && cube->image.img)
		mlx_destroy_image(cube->mlx, cube->image.img);
	if (cube->mlx && cube->win)
		mlx_destroy_window(cube->mlx, cube->win);
	exit(exit_code);
}

void	load_texture(t_cube *cube, t_texture *texture, char *path)
{
	texture->image.img = mlx_xpm_file_to_image(cube->mlx, path,
			&texture->width, &texture->height);
	if (!texture->image.img)
		quit_cube(cube, EXIT_FAILURE);
	texture->image.addr =  mlx_get_data_addr(
			texture->image.img,
			&texture->image.bits_per_pixel,
			&texture->image.size_line,
			&texture->image.endian);
}

int		initialize_player(t_player *player, t_cube *cube)
{
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->strafe_direction = 0;
	player->walk_speed = WALK_SPEED;
	player->turn_speed = TURN_SPEED * (PI / 180);
	cube->map.player.x = cube->map.tile_width *
		cube->map.player.map_x + cube->map.tile_width / 2;
	cube->map.player.y = cube->map.tile_height *
		cube->map.player.map_y + cube->map.tile_height / 2;
	return (0);
}

int		initialize_sprites(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < cube->map.sprites)
	{
		cube->sprites[i].x = cube->map.tile_width *
			cube->sprites[i].map_x + cube->map.tile_width / 2;
		cube->sprites[i].y = cube->map.tile_height *
			cube->sprites[i].map_y + cube->map.tile_height / 2;
		i++;
	}
	return (0);
}

int		initialize_assets(t_cube *cube)
{
	if (cube->width < cube->map.width ||
			cube->height < cube->map.height)
		quit_cube(cube, EXIT_FAILURE);
	cube->map.tile_width = cube->width / cube->map.width;
	cube->map.tile_height = cube->height / cube->map.height;
	initialize_player(&cube->map.player, cube);
	initialize_sprites(cube);
	return (0);
}

int		initialize_image(t_cube *cube)
{
	cube->image.img = mlx_new_image(cube->mlx, cube->width,
			cube->height);
	cube->image.addr = mlx_get_data_addr(
			cube->image.img,
			&cube->image.bits_per_pixel,
			&cube->image.size_line, 
			&cube->image.endian);
	load_texture(cube, &cube->texture[EAST], cube->map.paths[EAST]);
	load_texture(cube, &cube->texture[WEST], cube->map.paths[WEST]);
	load_texture(cube, &cube->texture[SOUTH], cube->map.paths[SOUTH] );
	load_texture(cube, &cube->texture[NORTH], cube->map.paths[NORTH]);
	load_texture(cube, &cube->texture[SPRITE], cube->map.paths[SPRITE]);
	return (0);
}

int		initialize_cube(t_cube *cube)
{
	int	width;
	int	height;

	cube->mlx = mlx_init();
	mlx_get_screen_size(cube->mlx, &width, &height);
	cube->width = min(cube->width, width);
	cube->height = min(cube->height, height);
	cube->win = mlx_new_window(cube->mlx, cube->width,
			cube->height, WINDOW_TITLE);
	cube->rays = malloc(sizeof(t_ray) * cube->width);
	if (cube->rays == NULL)
		quit_cube(cube, EXIT_FAILURE);
	cube->fov_angle = FOV * (PI / 180);
	cube->half_fov_angle = (FOV / 2)  * (PI / 180);
	cube->angle_step = cube->fov_angle / cube->width;
	cube->dist_proj_plane = (cube->width / 2) / tan(cube->half_fov_angle);
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

void	cast_all_rays(t_cube *cube)
{
	float	ray_angle;
	int		column;

	ray_angle = cube->map.player.rotation_angle - cube->half_fov_angle;
	column = 0;
	while (column < cube->width)
	{
		cast_ray(ray_angle, column, &cube->map, cube->rays);
		ray_angle += cube->angle_step;
		column++;
	}
}

int		grid_color(int row, int col, t_cube *cube)
{
	return (cube->map.grid[row][col] == 1 ? 0xffffffff : 0xff000000);
}

void	draw_minimap(t_cube *cube)
{
	t_point start;
	t_point end;
	int	row;
	int	col;
	t_point scaled;

	start.y = 0;
	start.x = 0;
	while (start.y < cube->height)
	{
		start.x = 0;
		while (start.x < cube->width)
		{
			row = start.y / cube->map.tile_height;
			col = start.x / cube->map.tile_width;
			if (row < cube->map.height && col < cube->map.width)
			{
				scaled.x = start.x * MINIMAP_SCALE;
				scaled.y = start.y * MINIMAP_SCALE;
				end.x = scaled.x + cube->map.tile_width * MINIMAP_SCALE;
				end.y = scaled.y + cube->map.tile_height * MINIMAP_SCALE;
				draw_rectangle(cube, scaled, end, grid_color(row, col, cube));
			}
			start.x += cube->map.tile_width;
		}
		start.y += cube->map.tile_height;
	}
}

void	render_rays(t_ray *rays, t_cube *cube)
{
	int			i;
	int			color;
	t_point	start;
	t_point	end;

	i = 0;
	color = 0xffff0000;
	while (i < cube->width)
	{
		start.x = cube->map.player.x * MINIMAP_SCALE;
		start.y = cube->map.player.y * MINIMAP_SCALE;
		end.x = rays[i].wall_hit_x * MINIMAP_SCALE;
		end.y = rays[i].wall_hit_y * MINIMAP_SCALE;
		draw_line(cube, start, end, color);
		i++;
	}
}

void	move_player(t_player *player, t_map *map, t_cube *cube)
{
	float	move_step;
	float	new_x;
	float	new_y;
	float	strafe_angle;
	float	strafe_step;
	int		**grid;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	player->rotation_angle = normalize_angle(player->rotation_angle);
	strafe_step = player->strafe_direction * player->walk_speed;
	strafe_angle = 0.5 * PI * (player->strafe_direction != 0);
	move_step = player->walk_direction * player->walk_speed; 
	new_x = player->x + cos(player->rotation_angle) * move_step + cos(player->rotation_angle + strafe_angle) * strafe_step;
	new_y = player->y + sin(player->rotation_angle) * move_step + sin(player->rotation_angle + strafe_angle) * strafe_step;
	grid = cube->map.grid;

	if (grid[(int)(new_y / map->tile_height)][(int)(new_x / map->tile_width)] == 0 &&
			grid[(int)((new_y - 1) / map->tile_height)][(int)(new_x / map->tile_width)] == 0 &&
			grid[(int)(new_y / map->tile_height)][(int)((new_x - 1) / map->tile_width)] == 0)
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	draw_player(t_cube *cube, t_player *player)
{
	t_point	start;
	t_point	end;

	start.x = (player->x - 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
	start.y = (player->y - 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
	end.x = (player->x + 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
	end.y = (player->y + 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
	draw_rectangle(cube, start, end, 0xffffff00); 
	start.x = (player->x) * MINIMAP_SCALE;
	start.y = (player->y) * MINIMAP_SCALE;
	end.x = start.x + cos(player->rotation_angle) * 40 * MINIMAP_SCALE;
	end.y = start.y + sin(player->rotation_angle) * 40 * MINIMAP_SCALE;
	draw_line(cube, start, end, 0xffffffff);
}

void	draw_sprites_minimap(t_cube *cube)
{
	t_point start;
	t_point end;
	int		i;

	i = 0;
	while (i < cube->map.sprites)
	{
		start.x = (cube->sprites[i].x - 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
		start.y = (cube->sprites[i].y - 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
		end.x = (cube->sprites[i].x + 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
		end.y = (cube->sprites[i].y + 20 * MINIMAP_SCALE) * MINIMAP_SCALE;
		draw_rectangle(cube, start, end, 0xff0000ff);
		i++;
	}
}

float	normalize_angle(float angle)
{
	angle = remainderf(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

int		map_has_wall_at(int x, int y, t_map *map)
{
	int	row;
	int	col;

	if (x < 0 || x >= map->tile_width * map->width ||
			y < 0 || y >= map->tile_height * map->height)
		return (TRUE);
	row = y / map->tile_height;
	col = x / map->tile_width;
	return (map->grid[row][col] == 1);
}

float	distance_between_points(float x1, float x2, float y1, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
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
	float	horz_hit_distance;

	int		found_vert_wall_hit;
	float	vert_wall_hit_x;
	float	vert_wall_hit_y;
	float	next_vert_touch_x;
	float	next_vert_touch_y;
	float	vert_hit_distance;

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
	yintercept = (int)(map->player.y / map->tile_height) * map->tile_height;
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
			next_horz_touch_x < map->tile_width * map->width &&
			next_horz_touch_y >= 0 &&
			next_horz_touch_y < map->tile_height * map->tile_height)
	{
		x_to_check = next_horz_touch_x;
		y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 1);

		if (map_has_wall_at(x_to_check, y_to_check, map))
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
	xintercept = (int)(map->player.x / map->tile_width) * map->tile_width;
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
			next_vert_touch_x < map->tile_width * map->width &&
			next_vert_touch_y >= 0 &&
			next_vert_touch_y < map->tile_height * map->height)
	{
		x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 1);
		y_to_check = next_vert_touch_y;

		if (map_has_wall_at(x_to_check, y_to_check, map))
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

	// Calculate both horizontal and vertical  distances and choose the  smallest one

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
		rays[column].distance = vert_hit_distance;
		rays[column].wall_hit_x = vert_wall_hit_x;
		rays[column].wall_hit_y = vert_wall_hit_y;
		rays[column].was_hit_vert = TRUE;
		rays[column].was_hit_horz = FALSE;
	}
	else
	{
		rays[column].distance = horz_hit_distance;
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

int		initialize_hooks(t_cube *cube)
{
	mlx_hook(cube->win, ClientMessage, StructureNotifyMask,
			close_window, cube);
	mlx_hook(cube->win, KeyPress, KeyPressMask, key_press, cube);
	mlx_hook(cube->win, KeyRelease, KeyReleaseMask, key_release, cube);
	return (0);
}

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

int		project_walls(t_cube *cube)
{
	int		i;
	int		y;
	int		wall_strip_height;
	float	projected_wall_height;
	float	perp_distance;
	int		wall_top_pixel;
	int		wall_bottom_pixel;

	int		texel_color;
	int		texture_offset_x;
	int		texture_offset_y;
	int		distance_from_top;

	int		side;
	i = 0;
	while (i < cube->width)
	{
		perp_distance = cube->rays[i].distance * cos(cube->rays[i].ray_angle - cube->map.player.rotation_angle);
		projected_wall_height = (cube->map.tile_height / perp_distance) * cube->dist_proj_plane;
		wall_strip_height = projected_wall_height;
		wall_top_pixel = (cube->height / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		wall_bottom_pixel = (cube->height / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > cube->height ? cube->height : wall_bottom_pixel;
		
		// Draw ceiling
		y = 0;
		while (y < wall_top_pixel)
		{
			pixel_put(&cube->image, i, y, cube->map.ceil_color);
			y++;
		}

		// Calculate texture_offset_x
		side = wall_side(&cube->rays[i]);
		if (cube->rays[i].was_hit_vert)
		{
			// perform offset for the vertical hit
			texture_offset_x = (int)cube->rays[i].wall_hit_y % cube->texture[side].height;
		}
		else
		{
			// perform offset for the horizontal hit
			texture_offset_x = (int)cube->rays[i].wall_hit_x % cube->texture[side].width;
		}

		// Draw walls
		y = wall_top_pixel;
		while (y < wall_bottom_pixel)
		{
			// Calculate texture_offset_y
			distance_from_top = y + (wall_strip_height / 2) - (cube->height / 2);
			texture_offset_y = distance_from_top * (cube->texture[side].height / (float)wall_strip_height);

			// Set the color of the wall based on the color from the texture
			texel_color = pixel_get(&cube->texture[side].image, texture_offset_x, texture_offset_y);
			pixel_put(&cube->image, i, y, texel_color);
			y++;
		}
		// Draw floor
		y = wall_bottom_pixel;
		while (y < cube->height)
		{
			pixel_put(&cube->image, i ,y, cube->map.floor_color);
			y++;
		}

		i++;
	}
	return (0);
}

int		calculate_sprite_angle(t_cube *cube)
{
	int		i;

	i = 0;
	while (i < cube->map.sprites)
	{
		cube->sprites[i].dy = cube->sprites[i].y - cube->map.player.y;
		cube->sprites[i].dx = cube->sprites[i].x - cube->map.player.x;
		cube->sprites[i].sprite_dir = atan2(cube->sprites[i].dy, cube->sprites[i].dx);
		if (cube->sprites[i].sprite_dir - cube->map.player.rotation_angle > PI)
			cube->sprites[i].sprite_dir -= TWO_PI;
		if (cube->sprites[i].sprite_dir - cube->map.player.rotation_angle < -PI)
			cube->sprites[i].sprite_dir += TWO_PI;
		cube->sprites[i].player_dist = distance_between_points(cube->map.player.x,
				cube->sprites[i].x, cube->map.player.y, cube->sprites[i].y);
		i++;
	}
	return (0);
}

int		sort_sprites(t_cube *cube)
{
	int			i;
	int			len;
	int			swap;
	t_sprite	temp;

	swap = -1;
	len = cube->map.sprites;
	while (swap)
	{
		swap = 0;
		i = 0;
		while (i + 1 < len)
		{
			if (cube->sprites[i].player_dist < cube->sprites[i + 1].player_dist)
			{
				temp = cube->sprites[i];
				cube->sprites[i] = cube->sprites[i + 1];
				cube->sprites[i + 1] = temp;
				swap++;
			}
			i++;
			len--;
		}
	}
	return (0);
}

void	render_sprite(t_cube *cube, int sprite_idx, int texture_id)
{
	int	sprite_size;
	int	h_offset;
	int	v_offset;
	int	i;
	int	j;

	sprite_size = cube->height / cube->sprites[sprite_idx].player_dist *
						cube->texture[texture_id].height;
	h_offset = (cube->sprites[sprite_idx].sprite_dir -
			cube->map.player.rotation_angle) *
			cube->width + (cube->width / 2) - (sprite_size / 2);
	v_offset = (cube->height / 2) - (sprite_size / 2);
	
	i = 0;
	while (i < sprite_size)
	{
        if ((h_offset + i >= 0 && h_offset + i < cube->width) &&
			(cube->rays[h_offset + i].distance > cube->sprites[sprite_idx].player_dist))
		{
			j = 0;
			while (j < sprite_size)
			{
				if (v_offset + j >= 0 && v_offset + j < cube->height)
				{
					int color = pixel_get(&cube->texture[texture_id].image,
							i * cube->texture[texture_id].height / sprite_size,
							j*cube->texture[texture_id].width/sprite_size);
					if (color)
						pixel_put(&cube->image, h_offset+i, v_offset+j, color);
				}
				j++;
			}
        }
		i++;
    }
}

int		draw_sprites(t_cube *cube)
{
	int	sprite_idx;

	calculate_sprite_angle(cube);
	sort_sprites(cube);
	sprite_idx = 0;
	while (sprite_idx < cube->map.sprites)
	{
		render_sprite(cube, sprite_idx, cube->sprites[sprite_idx].texture_id);
		sprite_idx++;
	}
	return (0);
}

int		render_cube(t_cube *cube)
{
	project_walls(cube);
	draw_sprites(cube);
	draw_minimap(cube);
	render_rays(cube->rays, cube);
	draw_player(cube, &cube->map.player);
	draw_sprites_minimap(cube);
	return (0);
}

int		update_cube(t_cube *cube)
{
	move_player(&cube->map.player, &cube->map, cube);
	cast_all_rays(cube);
	render_cube(cube);
	mlx_put_image_to_window(cube->mlx, cube->win,
			cube->image.img, 0, 0);
	mlx_do_sync(cube->mlx);
	return (0);
}

void	print_map(t_cube *cube)
{
	printf("Cube width: %d\n", cube->width);
	printf("Cube height: %d\n", cube->height);
	printf("Number of sprites: %d\n", cube->map.sprites);
	printf("Ceil color: alfa=%d, red=%d, green=%d, blue=%d, color=%d\n",
			get_t(cube->map.ceil_color), get_r(cube->map.ceil_color),
			get_g(cube->map.ceil_color), get_b(cube->map.ceil_color),
			cube->map.ceil_color);
	printf("Floor color: alfa=%d, red=%d, green=%d, blue=%d, color=%d\n",
			get_t(cube->map.floor_color), get_r(cube->map.floor_color),
			get_g(cube->map.floor_color), get_b(cube->map.floor_color),
			cube->map.floor_color);
	printf("Map width: %d\n", cube->map.width);
	printf("Map height: %d\n", cube->map.height);
	for (int i = 0; i < TEXTURES; i++)
	{
		printf("%s\n", cube->map.paths[i]);
	}
	for (int i = 0;i < cube->map.sprites; i++)
	{
		printf("Sprite map_y %d\n", cube->sprites[i].map_y);
		printf("Sprite map_x %d\n", cube->sprites[i].map_x);
		printf("Sprite texture %d\n", cube->sprites[i].texture_id);
	}
	printf("Player map_y=%d, map_x=%d\n", cube->map.player.map_y, cube->map.player.map_x);
	printf("Player position %f\n", cube->map.player.rotation_angle);
	printf("Map tile width: %d\n",
		(cube->map.tile_width = cube->width / cube->map.width));
	printf("Map tile height: %d\n",
		(cube->map.tile_height = cube->height / cube->map.height));
	printf("Grid\n");
	for (int y = 0; y < cube->map.height; y++)
	{
		for (int x = 0; x < cube->map.width; x++)
		{
			if (cube->map.grid[y][x] != 2)
				printf("%d", cube->map.grid[y][x]);
			else
				printf("%c", ' ');
		}
		printf("\n");
	}
}

/*
**
**	DESCRIPTION
**
**	RETURN VALUES
**
*/

int		main(int argc, char **argv)
{
	t_cube	cube;

	if (argc == 1)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" map.cub\n", 2);
		return (1);
	}
	ft_bzero(&cube, sizeof(cube));
	parse_cub(argv[1], &cube);
	initialize_cube(&cube);
	initialize_assets(&cube);
	initialize_image(&cube);
	initialize_hooks(&cube);
	update_cube(&cube);
	save_bitmap(&cube);
	print_map(&cube);
	mlx_loop_hook(cube.mlx, update_cube, &cube);
	mlx_loop(cube.mlx);
}
