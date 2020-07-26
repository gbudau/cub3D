/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 18:23:05 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/26 19:14:17 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static void	calculate_tex_off_x(int	i, t_wall_strip *w, t_cub *cub)
{
	if (cub->rays[i].was_hit_vert)
	{
		w->tex_off_x = (int)cub->rays[i].wall_hit_y %
													cub->texture[w->side].height;
	}
	else
	{
		w->tex_off_x = (int)cub->rays[i].wall_hit_x %
													cub->texture[w->side].width;
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
