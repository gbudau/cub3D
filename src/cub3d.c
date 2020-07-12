/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:38:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/12 14:04:28 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>


int		update_cube(t_cube *cube);

int map[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int		initialize_player(t_player *player, t_window *window)
{
	player->x = window->width / 2;
	player->y = window->height / 2;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->strafe_direction = 0;
	player->rotation_angle = PI_2;
	player->walk_speed = WALK_SPEED;
	player->turn_speed = RADIAN_ANGLE;
	return (0);
}

int		parse_map(t_cube *cube)
{
	// TODO: Check if window.width < map.width
	// or window.height < map.height and exit with an error
	cube->window.width = 800;
	cube->window.height = 600;
	cube->map.ceil_color = 0xff666666;
	cube->map.floor_color = 0xff663300;
	cube->map.width = 20;
	cube->map.height = 15;
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
	return (0);
}

int		key_press(int	keycode, t_cube *cube)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(cube->mlx, cube->image.img);
		mlx_destroy_window(cube->mlx, cube->window.win);
		exit(EXIT_SUCCESS);
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

int		get_map_color(int row, int col, t_cube *cube)
{
	(void)cube;
	return (map[row][col] == 0 ? 0x00000000 : 0xffffffff);
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
			cube->map.color = get_map_color(row, col, cube);
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

void	move_player(t_player *player)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;
	float	strafe_angle;
	float	strafe_step;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	strafe_step = player->strafe_direction * player->walk_speed;
	strafe_angle = PI_2 * !!player->strafe_direction;
	move_step = player->walk_direction * player->walk_speed; 
	new_player_x = player->x + cos(player->rotation_angle) * move_step + cos(player->rotation_angle + strafe_angle) * strafe_step;
	new_player_y = player->y + sin(player->rotation_angle) * move_step + sin(player->rotation_angle + strafe_angle) * strafe_step;

	player->x = new_player_x;
	player->y = new_player_y;
}

void	draw_player(t_cube *cube, t_player *player)
{
	t_position	start;
	t_position	end;

	start.x = (player->x - 3 * MINIMAP_SCALE) * MINIMAP_SCALE;
	start.y = (player->y - 3 * MINIMAP_SCALE) * MINIMAP_SCALE;
	end.x = start.x + 6 * MINIMAP_SCALE;
	end.y = start.y + 6 * MINIMAP_SCALE;
	cube->map.color = 0xffff0000;
	draw_rectangle(cube, start, end); 
	start.x = (player->x) * MINIMAP_SCALE;
	start.y = (player->y) * MINIMAP_SCALE;
	end.x = start.x + cos(player->rotation_angle) * 40 * MINIMAP_SCALE;
	end.y = start.y + sin(player->rotation_angle) * 40 * MINIMAP_SCALE;
	draw_line(cube, start, end);
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
	draw_player(cube, &cube->map.player);
	move_player(&cube->map.player);
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
