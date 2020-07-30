/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_walls_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 18:23:05 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/30 21:31:10 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

static void	calculate_wall(int i, t_wall_strip *w, t_cub *cub)
{
	w->perp_dist = cub->rays[i].dist * cos(cub->rays[i].ray_angle -
			cub->map.player.rotation_angle);
	w->proj_height = (TILE_SIZE / w->perp_dist) * cub->dist_proj_plane;
	w->strip_height = w->proj_height;
	w->top_pix = (cub->height / 2) - (w->strip_height / 2);
	w->top_pix = w->top_pix < 0 ? 0 : w->top_pix;
	w->bot_pix = (cub->height / 2) + (w->strip_height / 2);
	w->bot_pix = w->bot_pix > cub->height ? cub->height : w->bot_pix;
}

static void	calculate_tex_off_x(int i, t_wall_strip *w, t_cub *cub)
{
	if (cub->rays[i].was_hit_vert)
	{
		w->tex_off_x = (int)cub->rays[i].wall_hit_y % TILE_SIZE;
		w->tex_off_x = w->tex_off_x * cub->texture[w->side].width / TILE_SIZE;
	}
	else
	{
		w->tex_off_x = (int)cub->rays[i].wall_hit_x % TILE_SIZE;
		w->tex_off_x = w->tex_off_x * cub->texture[w->side].width / TILE_SIZE;
	}
}

static void	draw_wall(int i, t_wall_strip *w, t_cub *cub)
{
	int y;

	y = w->top_pix;
	while (y < w->bot_pix)
	{
		w->top_dist = y + (w->strip_height / 2) - (cub->height / 2);
		w->tex_off_y = w->top_dist * (cub->texture[w->side].height /
														(float)w->strip_height);
		w->color = pixel_get(&cub->texture[w->side].image,
													w->tex_off_x, w->tex_off_y);
		pixel_put(&cub->image, i, y, w->color);
		y++;
	}
}

void		project_walls(t_cub *cub)
{
	int				i;
	t_wall_strip	w;

	i = 0;
	while (i < cub->width)
	{
		calculate_wall(i, &w, cub);
		draw_ceiling(i, &w, cub);
		w.side = wall_side(&cub->rays[i]);
		calculate_tex_off_x(i, &w, cub);
		draw_wall(i, &w, cub);
		draw_floor(i, &w, cub);
		i++;
	}
}
