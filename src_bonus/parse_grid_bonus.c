/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:50:51 by gbudau            #+#    #+#             */
/*   Updated: 2020/08/06 12:09:48 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

static void	set_rotation_angle(int position, t_cub *cub)
{
	if (position == 'N')
		cub->map.player.rotation_angle = PI / 2 * 3;
	else if (position == 'S')
		cub->map.player.rotation_angle = PI / 2;
	else if (position == 'W')
		cub->map.player.rotation_angle = PI;
	else if (position == 'E')
		cub->map.player.rotation_angle = 0;
}

static int	check_row(char *str, t_cub *cub)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(VALID_MAP_CHARS, str[i]) == NULL)
			return (-1);
		if (str[i] == '2' || str[i] == '3')
			cub->map.sprites++;
		if (ft_strchr(SPAWN_ORIENTATION, str[i]))
		{
			if (cub->map.player_found != 0)
				return (-1);
			cub->map.player_found++;
			cub->map.player.map_x = i;
			cub->map.player.map_y = cub->map.height;
			set_rotation_angle(str[i], cub);
			str[i] = '0';
		}
		i++;
	}
	cub->map.height++;
	cub->map.width = ft_max(i, cub->map.width);
	return (i == 0 ? -1 : 0);
}

void		parse_grid(t_list *trav, t_list *head, t_cub *cub)
{
	int		open;
	t_list	*lst;

	while (trav && *(char *)trav->content == '\0')
		trav = trav->next;
	lst = trav;
	while (lst)
	{
		if (check_row(lst->content, cub) == -1)
			free_lst_quit(head, cub, ERR_MAP);
		lst = lst->next;
	}
	if (cub->map.player_found != 1 ||
			cub->width <= 0 ||
			cub->height <= 0)
		free_lst_quit(head, cub, ERR_MAP);
	if (save_map(trav, cub) == -1)
		free_lst_quit(head, cub, ERR_MEM);
	open = FALSE;
	boundary_fill(cub->map.player.map_x, cub->map.player.map_y, &open, cub);
	if (open == TRUE)
		free_lst_quit(head, cub, ERR_MAP);
	rev_boundary_fill(cub);
}
