/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:12:11 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/31 01:32:02 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

static int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		quit_cub(cub, EXIT_SUCCESS, "");
	if (keycode == KEY_W)
		cub->map.player.walk_direction = 1;
	if (keycode == KEY_S)
		cub->map.player.walk_direction = -1;
	if (keycode == KEY_D)
		cub->map.player.strafe_direction = 1;
	if (keycode == KEY_A)
		cub->map.player.strafe_direction = -1;
	if (keycode == KEY_AR_R)
		cub->map.player.turn_direction = 1;
	if (keycode == KEY_AR_L)
		cub->map.player.turn_direction = -1;
	if (keycode == KEY_M)
		cub->minimap = !cub->minimap;
	return (0);
}

static int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->map.player.walk_direction = 0;
	if (keycode == KEY_S)
		cub->map.player.walk_direction = 0;
	if (keycode == KEY_D)
		cub->map.player.strafe_direction = 0;
	if (keycode == KEY_A)
		cub->map.player.strafe_direction = 0;
	if (keycode == KEY_AR_R)
		cub->map.player.turn_direction = 0;
	if (keycode == KEY_AR_L)
		cub->map.player.turn_direction = 0;
	return (0);
}

static int	close_window(int keycode, t_cub *cub)
{
	(void)keycode;
	(void)cub;
	exit(EXIT_SUCCESS);
	return (0);
}

void		set_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 33, (1L << 17),
			close_window, cub);
	mlx_hook(cub->win, 2, (1L << 0), key_press, cub);
	mlx_hook(cub->win, 3, (1L << 1), key_release, cub);
}
