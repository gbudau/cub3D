/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 22:08:11 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/29 21:58:12 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		draw_rays_minimap(t_ray *rays, t_cub *cub)
{
	int		i;
	t_point	start;
	t_point	end;

	i = 0;
	while (i < cub->width)
	{
		start.x = cub->map.player.x * MINIMAP_SCALE;
		start.y = cub->map.player.y * MINIMAP_SCALE;
		end.x = rays[i].wall_hit_x * MINIMAP_SCALE;
		end.y = rays[i].wall_hit_y * MINIMAP_SCALE;
		draw_line(cub, start, end, RAYS_COL);
		i++;
	}
}

void		draw_sprites_minimap(t_cub *cub)
{
	t_point start;
	t_point end;
	int		i;

	i = 0;
	while (i < cub->map.sprites)
	{
		start.x = ((cub->sprites[i].x - 10) * MINIMAP_SCALE);
		start.y = ((cub->sprites[i].y - 10) * MINIMAP_SCALE);
		end.x = ((cub->sprites[i].x + 10) * MINIMAP_SCALE);
		end.y = ((cub->sprites[i].y + 10) * MINIMAP_SCALE);
		draw_rectangle(cub, start, end, SPRITE_COL);
		i++;
	}
}

void		draw_player_minimap(t_cub *cub, t_player *player)
{
	t_point	start;
	t_point	end;

	start.x = ((player->x - 10) * MINIMAP_SCALE);
	start.y = ((player->y - 10) * MINIMAP_SCALE);
	end.x = ((player->x + 10) * MINIMAP_SCALE);
	end.y = ((player->y + 10) * MINIMAP_SCALE);
	draw_rectangle(cub, start, end, PLAYER_COL);
	start.x = (player->x) * MINIMAP_SCALE;
	start.y = (player->y) * MINIMAP_SCALE;
	end.x = start.x + cos(player->rotation_angle) * 40 * MINIMAP_SCALE;
	end.y = start.y + sin(player->rotation_angle) * 40 * MINIMAP_SCALE;
	draw_line(cub, start, end, PLAYER_DIR_COL);
}

static void	draw_tile(t_point *start, t_point *end, int color, t_cub *cub)
{
	t_point	scaled;

	scaled.x = start->x * MINIMAP_SCALE;
	scaled.y = start->y * MINIMAP_SCALE;
	end->x = scaled.x + TILE_SIZE * MINIMAP_SCALE;
	end->y = scaled.y + TILE_SIZE * MINIMAP_SCALE;
	draw_rectangle(cub, scaled, *end, color);
}

void		draw_minimap(t_cub *cub)
{
	t_point	start;
	t_point	end;
	int		row;
	int		col;
	int		color;

	start.y = 0;
	start.x = 0;
	while (start.y < cub->map.height * TILE_SIZE)
	{
		start.x = 0;
		while (start.x < cub->map.width * TILE_SIZE)
		{
			row = start.y / TILE_SIZE;
			col = start.x / TILE_SIZE;
			if (row < cub->map.height && col < cub->map.width)
			{
				color = grid_color(row, col, cub);
				draw_tile(&start, &end, color, cub);
			}
			start.x += TILE_SIZE;
		}
		start.y += TILE_SIZE;
	}
}
