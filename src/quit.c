/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:56:08 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/26 16:56:36 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	quit_cub(t_cub *cub, int exit_code)
{
	int	i;

	free(cub->rays);
	free(cub->sprites);
	ft_free_int_matrix(cub->map.grid, cub->map.height);
	i = 0;
	while (i < TEXTURES)
	{
		free(cub->map.paths[i]);
		if (cub->texture[i].image.img)
			mlx_destroy_image(cub->mlx, cub->texture[i].image.img);
		i++;
	}
	if (cub->mlx && cub->image.img)
		mlx_destroy_image(cub->mlx, cub->image.img);
	if (cub->mlx && cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	ft_bzero(cub, sizeof(t_cub));
	exit(exit_code);
}
