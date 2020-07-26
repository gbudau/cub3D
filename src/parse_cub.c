/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:53:27 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/26 16:53:41 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_lst_quit(t_list *head, t_cub *cub)
{
	ft_lstclear(&head, free);
	quit_cub(cub, EXIT_FAILURE);
}

void	free_info_lst_quit(char **info, t_list *head, t_cub *cub)
{
	ft_free_strarr(info);
	free_lst_quit(head, cub);
}

void	lst_add_line(char *line, t_list **head, t_cub *cub)
{
	t_list	*node;

	node = NULL;
	if ((node = ft_lstnew(line)) == NULL)
		free_lst_quit(*head, cub);
	ft_lstadd_front(head, node);
}

int		strlen_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (i);
}

int		parse_resolution(int *flags, t_cub *cub)
{
	char	**info;
	int		len_width;
	int		len_height;

	info = cub->info;
	if (*flags & RESOLUTION || ft_strarrlen(info) != 3 ||
			(len_width = strlen_isdigit(info[1])) < 1 ||
			(len_height = strlen_isdigit(info[2])) < 1)
		return (-1);
	else
	{
		cub->width = len_width < 10 ? ft_atoi(info[1]) : INT_MAX;
		cub->height = len_height < 10 ? ft_atoi(info[2]) : INT_MAX;
	}
	ft_free_strarr(info);
	*flags |= RESOLUTION;
	return (0);
}

int		save_texture(int *flags, int flag, int tex_id, t_cub *cub)
{
	if (*flags & flag || ft_strarrlen(cub->info) != 2)
		return (-1);
	cub->map.paths[tex_id] = cub->info[1];
	free(cub->info[0]);
	free(cub->info);
	*flags |= flag;
	return (0);
}

int		parse_texture(int *flags, t_cub *cub)
{
	char	**info;

	info = cub->info;
	if (!ft_strcmp(*info, "NO"))
		return (save_texture(flags, NORTH_TEX, NORTH, cub));
	else if (!ft_strcmp(*info, "SO"))
		return (save_texture(flags, SOUTH_TEX, SOUTH, cub));
	else if (!ft_strcmp(*info, "WE"))
		return (save_texture(flags, WEST_TEX, WEST, cub));
	else if (!ft_strcmp(*info, "EA"))
		return (save_texture(flags, EAST_TEX, EAST, cub));
	else
		return (save_texture(flags, SPRITE_TEX, SPRITE, cub));
}

int		str_to_color(char *str)
{
	int		color;
	int		len;

	len = strlen_isdigit(str);
	if (len < 0 || len > 3)
		return (-1);
	color = ft_atoi(str);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

int		create_color(char **rgb, int *color)
{
	int		red;
	int		green;
	int		blue;

	red = str_to_color(rgb[0]);
	if (red < 0)
		return (-1);
	blue = str_to_color(rgb[1]);
	if (blue < 0)
		return (-1);
	green = str_to_color(rgb[2]);
	if (green < 0)
		return (-1);
	*color = create_trgb(255, red, blue, green);
	return (0);
}

int		save_color(int *flags, int flag, t_cub *cub)
{
	char	**rgb;
	int		color;

	if (*flags & flag || ft_strarrlen(cub->info) != 2 ||
			((rgb = ft_split(cub->info[1], ',')) == NULL))
		return (-1);
	if (ft_strarrlen(rgb) != 3 || (create_color(rgb, &color)) < 0)
	{
		ft_free_strarr(rgb);
		return (-1);
	}
	if (flag & CEIL_COL)
		cub->map.ceil_color = color;
	else
		cub->map.floor_color = color;
	ft_free_strarr(rgb);
	*flags |= flag;
	return (0);
}

int		parse_color(int *flags, t_cub *cub)
{
	char	**info;

	info = cub->info;
	if (!ft_strcmp(*info, "C"))
	{
		if (save_color(flags, CEIL_COL, cub) < 0)
			return (-1);
	}
	else
	{
		if (save_color(flags, FLOOR_COL, cub) < 0)
			return (-1);
	}
	ft_free_strarr(info);
	return (0);
}

void	parse_identifier(int *flags, t_list *head, t_cub *cub)
{
	char	**info;

	info = cub->info;
	if (!ft_strcmp(*info, "R"))
	{
		if (parse_resolution(flags, cub) == -1)
			free_info_lst_quit(info, head, cub);
	}
	else if (!ft_strcmp(*info, "NO") || !ft_strcmp(*info, "SO") ||
			!ft_strcmp(*info, "WE") || !ft_strcmp(*info, "EA") ||
			!ft_strcmp(*info, "S"))
	{
		if (parse_texture(flags, cub) == -1)
			free_info_lst_quit(info, head, cub);
	}
	else if (!ft_strcmp(*info, "F") || !ft_strcmp(*info, "C"))
	{
		if (parse_color(flags, cub) == -1)
			free_info_lst_quit(info, head, cub);
	}
	else
		free_info_lst_quit(info, head, cub);
}

void	parse_line(char *line, int *flags, t_list *head, t_cub *cub)
{
	if ((cub->info = ft_split(line, ' ')) == NULL)
		free_lst_quit(head, cub);
	if (*(cub->info))
	{
		parse_identifier(flags, head, cub);
	}
	else
		free(cub->info);
}

void	set_rotation_angle(int position, t_cub *cub)
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

int		check_row(char *str, t_cub *cub)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(VALID_MAP_CHARS, str[i]) == NULL)
			return (-1);
		if (str[i] == '2')
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
	return (i < 3 ? -1 : 0);
}

int		check_map(t_list *trav, t_cub *cub)
{
	while (trav)
	{
		if (check_row(trav->content, cub) == -1)
			return (-1);
		trav = trav->next;
	}
	return (0);
}

void	set_sprite(int x, int y, int i, t_cub *cub)
{
	cub->sprites[i].map_x = x;
	cub->sprites[i].map_y = y;
	cub->sprites[i].tex_id = SPRITE;
	cub->row[x] = '0';
}

int		save_sprite_positions(t_list *trav, t_cub *cub)
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

int		save_row(char *row, int y, t_cub *cub)
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

int		save_grid(t_list *trav, t_cub *cub)
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

int		save_map(t_list *trav, t_cub *cub)
{
	if (cub->map.sprites != 0)
		if (save_sprite_positions(trav, cub) == -1)
			return (-1);
	if (save_grid(trav, cub) == -1)
		return (-1);
	return (0);
}

t_list	*skip_empty_lines(t_list *trav)
{
	while (trav && *(char *)trav->content == '\0')
		trav = trav->next;
	return (trav);
}

void	parse_map(t_list *trav, t_list *head, t_cub *cub)
{
	int	open;

	trav = skip_empty_lines(trav);
	if (check_map(trav, cub) == -1)
		free_lst_quit(head, cub);
	if (cub->map.player_found != 1 ||
			cub->width <= 0 ||
			cub->height <= 0)
		free_lst_quit(head, cub);
	if (save_map(trav, cub) == -1)
		free_lst_quit(head, cub);
	open = FALSE;
	boundary_fill(cub->map.player.map_x, cub->map.player.map_y, &open, cub);
	if (open == TRUE)
		free_lst_quit(head, cub);
	rev_boundary_fill(cub);
}

void	parse_list(t_list *head, t_cub *cub)
{
	t_list	*trav;
	int		flags;

	flags = 0;
	trav = head;
	while (trav)
	{
		if (flags != IDENTIFIERS)
		{
			parse_line(trav->content, &flags, head, cub);
			trav = trav->next;
		}
		else
			break ;
	}
	if (flags != IDENTIFIERS)
		free_lst_quit(head, cub);
	parse_map(trav, head, cub);
}

void	parse_cub(char *path, t_cub *cub)
{
	int		fd;
	int		error;
	char	*line;
	t_list	*head;

	head = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		quit_cub(cub, EXIT_FAILURE);
	line = NULL;
	while ((error = get_next_line(fd, &line)) > 0)
		lst_add_line(line, &head, cub);
	if (error != -1 && *line)
		lst_add_line(line, &head, cub);
	else
		free(line);
	ft_lstrev(&head);
	if (close(fd))
		free_lst_quit(head, cub);
	parse_list(head, cub);
	ft_lstclear(&head, free);
}
