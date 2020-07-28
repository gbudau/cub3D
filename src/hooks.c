/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:12:11 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/27 19:03:01 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		quit_cub(cub, EXIT_SUCCESS);
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
	mlx_hook(cub->win, ClientMessage, StructureNotifyMask,
			close_window, cub);
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_press, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, key_release, cub);
}
