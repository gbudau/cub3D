/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:34:33 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/27 21:04:11 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_collision(t_cub *cub, float x, float y)
{
	int	**grid;

	if (x < 1 || y < 1 || x >= cub->map.width * TILE_SIZE ||
			y >= cub->map.height * TILE_SIZE)
		return (1);
	grid = cub->map.grid;
	if (grid[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == 0 &&
			grid[(int)((y - 1) / TILE_SIZE)][(int)(x / TILE_SIZE)] == 0 &&
			grid[(int)(y / TILE_SIZE)][(int)((x - 1) / TILE_SIZE)] == 0)
		return (0);
	return (1);
}

void		move_player(t_player *player, t_cub *cub)
{
	float	move_step;
	float	new_x;
	float	new_y;
	float	strafe_angle;
	float	strafe_step;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	player->rotation_angle = normalize_angle(player->rotation_angle);
	strafe_step = player->strafe_direction * player->walk_speed;
	strafe_angle = 0.5 * PI * (player->strafe_direction != 0);
	move_step = player->walk_direction * player->walk_speed;
	new_x = player->x + cos(player->rotation_angle) * move_step +
		cos(player->rotation_angle + strafe_angle) * strafe_step;
	new_y = player->y + sin(player->rotation_angle) * move_step +
		sin(player->rotation_angle + strafe_angle) * strafe_step;
	if (check_collision(cub, new_x, new_y) == 0)
	{
		player->x = new_x;
		player->y = new_y;
	}
}
