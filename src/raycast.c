/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:40:20 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/26 16:40:33 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cast_rays(t_cub *cub)
{
	float	ray_angle;
	int		column;

	ray_angle = cub->map.player.rotation_angle - cub->half_fov_angle;
	column = 0;
	while (column < cub->width)
	{
		cast_ray(ray_angle, column, &cub->map, cub->rays);
		ray_angle += cub->angle_step;
		column++;
	}
}
