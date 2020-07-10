/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_image_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:06:18 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/10 23:58:01 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_rectangle(t_cube *cube, t_position start, t_position end)
{
	int tmp;

	tmp = start.x;
	while (start.y < end.y && end.y <= cube->window.height)
	{
		start.x = tmp;
		while (start.x < end.x && end.x <= cube->window.width)
		{
			pixel_put(&cube->image, start.x, start.y, cube->map.color);
			start.x++;
		}
		start.y++;
	}
}
