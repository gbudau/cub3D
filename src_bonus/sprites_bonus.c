/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 21:04:23 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/29 21:48:53 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calculate_sprites(t_cub *cub)
{
	int			i;
	float		dx;
	float		dy;
	t_sprite	*sprite;
	t_player	*player;

	i = -1;
	player = &cub->map.player;
	while (++i < cub->map.sprites)
	{
		sprite = &cub->sprites[i];
		dy = sprite->y - player->y;
		dx = sprite->x - player->x;
		sprite->direction = atan2(dy, dx);
		while (sprite->direction - player->rotation_angle > PI)
			sprite->direction -= TWO_PI;
		while (sprite->direction - player->rotation_angle < -PI)
			sprite->direction += TWO_PI;
		sprite->player_dist = points_dist(player->x,
				sprite->x, player->y, sprite->y);
		sprite->size = cub->width / sprite->player_dist * TILE_SIZE;
		sprite->y_off = (cub->height / 2) - (sprite->size / 2);
		sprite->x_off = (sprite->direction - player->rotation_angle) *
			cub->width / cub->fov_angle + (cub->width / 2) - (sprite->size / 2);
	}
}

static void	sort_sprites(t_cub *cub)
{
	int			i;
	int			len;
	int			swap;
	t_sprite	temp;

	swap = -1;
	len = cub->map.sprites;
	while (swap)
	{
		swap = 0;
		i = 0;
		while (i + 1 < len)
		{
			if (cub->sprites[i].player_dist < cub->sprites[i + 1].player_dist)
			{
				temp = cub->sprites[i];
				cub->sprites[i] = cub->sprites[i + 1];
				cub->sprites[i + 1] = temp;
				swap++;
			}
			i++;
		}
	}
}

static void	draw_sprite(t_cub *cub, int i, int tex_id)
{
	int			y;
	int			x;
	int			c;
	t_sprite	*s;

	y = -1;
	s = &cub->sprites[i];
	while (++y < s->size)
	{
		if (s->y_off + y >= 0 && s->y_off + y < cub->height && (x = -1))
		{
			while (++x < s->size)
			{
				if ((s->x_off + x >= 0 && s->x_off + x < cub->width) &&
					(cub->rays[s->x_off + x].dist > s->player_dist))
				{
					c = pixel_get(&cub->texture[tex_id].image,
							x * cub->texture[tex_id].height / s->size,
							y * cub->texture[tex_id].width / s->size);
					if (c)
						pixel_put(&cub->image, s->x_off + x, s->y_off + y, c);
				}
			}
		}
	}
}

void		draw_sprites(t_cub *cub)
{
	int	i;

	calculate_sprites(cub);
	sort_sprites(cub);
	i = 0;
	while (i < cub->map.sprites)
	{
		draw_sprite(cub, i, cub->sprites[i].tex_id);
		i++;
	}
}
