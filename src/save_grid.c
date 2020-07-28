/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:07:16 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/28 18:11:52 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	save_row(char *row, int y, t_cub *cub)
{
	int	x;
	int	**grid;
	int	*grid_row;

	if ((grid_row = malloc(sizeof(int) * cub->map.width)) == NULL)
		return (-1);
	grid = cub->map.grid;
	grid[y] = grid_row;
	x = 0;
	while (row[x])
	{
		if (row[x] == ' ')
			grid[y][x] = 2;
		else
			grid[y][x] = row[x] - '0';
		x++;
	}
	while (x < cub->map.width)
	{
		grid[y][x] = 2;
		x++;
	}
	return (0);
}

static int	save_grid(t_list *trav, t_cub *cub)
{
	int	y;

	cub->map.grid = malloc(sizeof(int *) * cub->map.height);
	if (cub->map.grid == NULL)
		return (-1);
	y = 0;
	while (trav)
	{
		cub->row = trav->content;
		if (save_row(cub->row, y, cub) == -1)
		{
			ft_free_int_matrix(cub->map.grid, y);
			cub->map.grid = NULL;
			return (-1);
		}
		y++;
		trav = trav->next;
	}
	return (0);
}

static void	set_sprite(int x, int y, int i, t_cub *cub)
{
	cub->sprites[i].map_x = x;
	cub->sprites[i].map_y = y;
	cub->sprites[i].tex_id = SPRITE;
	cub->row[x] = '0';
}

static int	save_sprite_positions(t_list *trav, t_cub *cub)
{
	int		y;
	int		x;
	int		i;

	if ((cub->sprites = malloc(sizeof(t_sprite) * cub->map.sprites)) == NULL)
		return (-1);
	y = 0;
	i = 0;
	while (trav)
	{
		cub->row = trav->content;
		x = 0;
		while (cub->row[x])
		{
			if (cub->row[x] == '2')
			{
				set_sprite(x, y, i, cub);
				i++;
			}
			x++;
		}
		y++;
		trav = trav->next;
	}
	return (0);
}

int			save_map(t_list *trav, t_cub *cub)
{
	if (cub->map.sprites != 0)
		if (save_sprite_positions(trav, cub) == -1)
			return (-1);
	if (save_grid(trav, cub) == -1)
		return (-1);
	return (0);
}
