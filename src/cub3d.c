/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:38:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/02 15:04:11 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#define WIDTH 600
#define HEIGHT 400

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3d");
	mlx_string_put(mlx, win, WIDTH / 2, HEIGHT / 2, 0xffffffff, "cub3d");
	mlx_loop(mlx);
}
