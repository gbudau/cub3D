/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:38:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/11 00:27:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

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
	player->position.x = window->width / 2;
	player->position.y = window->height / 2;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->strafe_direction = 0;
	player->rotation_angle = M_PI_2;
	player->walk_speed = 100;
	player->turn_speed = 45 * (RADIAN_ANGLE);
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
			cube->window.height, "cub3d");
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
		printf("%s\n", "Move forward");
	if (keycode == KEY_S)
		printf("%s\n", "Move backward");
	if (keycode == KEY_D)
		printf("%s\n", "Move right");
	if (keycode == KEY_A)
		printf("%s\n", "Move left");
	return (0);
}

int		key_release(int keycode, t_cube *cube)
{
	(void)cube;
	if (keycode == KEY_W)
		printf("%s\n", "Stop moving forward");
	if (keycode == KEY_S)
		printf("%s\n", "Stop moving backward");
	if (keycode == KEY_D)
		printf("%s\n", "Stop moving right");
	if (keycode == KEY_A)
		printf("%s\n", "Stop moving left");
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

void	draw_cube(t_cube *cube)
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
			// Delete this image2window later
			//mlx_put_image_to_window(cube->mlx, cube->window.win,
			//		cube->image.img, 0, 0);
			start.x += cube->map.tile_width;
		}
		start.y += cube->map.tile_height;
	}
}

void	draw_player(t_cube *cube)
{
	t_position	start;
	t_position	end;

	start.x = (cube->map.player.position.x - 3) * MINIMAP_SCALE;
	start.y = (cube->map.player.position.y - 3) * MINIMAP_SCALE;
	end.x = start.x + 6;
	end.y = start.y + 6;
	cube->map.color = 0xffff0000;
	draw_rectangle(cube, start, end); 
}

int		initialize_hooks(t_cube *cube)
{
	mlx_hook(cube->window.win, KeyPress, KeyPressMask, key_press, cube);
	mlx_hook(cube->window.win, DestroyNotify, StructureNotifyMask,
			close_window, cube);
	mlx_hook(cube->window.win, KeyRelease, KeyReleaseMask, key_release, cube);
	return (0);
}

int		update_cube(t_cube *cube)
{
	mlx_put_image_to_window(cube->mlx, cube->window.win,
			cube->image.img, 0, 0);
	return (0);
}

int		main(void)
{
	t_cube	cube;

	parse_map(&cube);
	initialize_cube(&cube);
	initialize_image(&cube);
	draw_cube(&cube);
	draw_player(&cube);
	update_cube(&cube);
	initialize_hooks(&cube);
	mlx_loop(cube.mlx);
}
