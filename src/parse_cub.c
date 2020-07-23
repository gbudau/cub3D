/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:53:27 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/23 16:00:41 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_lst_quit(t_list *head, t_cube *cube)
{
	ft_lstclear(&head, free);
	quit_cube(cube, EXIT_FAILURE);
}

void	free_info_lst_quit(char **info, t_list *head, t_cube *cube)
{
	ft_free_strarr(info);
	free_lst_quit(head, cube);
}

void	lst_add_line(char *line, t_list **head, t_cube *cube)
{
	t_list	*node;

	node = NULL;
	if ((node = ft_lstnew(line)) == NULL)
		free_lst_quit(*head, cube);
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

int		parse_resolution(int *flags, t_cube *cube)
{
	char	**info;
	int		len_width;
	int		len_height;

	info = cube->info;
	if (*flags & RESOLUTION || ft_strarrlen(info) != 3 ||
			(len_width = strlen_isdigit(info[1])) < 1 ||
			(len_height = strlen_isdigit(info[2])) < 1)
		return (-1);
	else
	{
		cube->width = len_width < 10 ? ft_atoi(info[1]) : INT_MAX;
		cube->height = len_height < 10 ? ft_atoi(info[2]) : INT_MAX;
	}
	ft_free_strarr(info);
	*flags |= RESOLUTION;
	return (0);
}

int		save_texture(int *flags, int flag, int texture_id, t_cube *cube)
{
	if (*flags & flag || ft_strarrlen(cube->info) != 2)
		return (-1);
	cube->map.paths[texture_id] = cube->info[1];
	free(cube->info[0]);
	free(cube->info);
	*flags |= flag;
	return (0);
}

int		parse_texture(int *flags, t_cube *cube)
{
	char	**info;

	info = cube->info;
	if (!ft_strcmp(*info, "NO"))
		return (save_texture(flags, NORTH_TEX, NORTH, cube));
	else if (!ft_strcmp(*info, "SO"))
		return (save_texture(flags, SOUTH_TEX, SOUTH, cube));
	else if (!ft_strcmp(*info, "WE"))
		return (save_texture(flags, WEST_TEX, WEST, cube));
	else if (!ft_strcmp(*info, "EA"))
		return (save_texture(flags, EAST_TEX, EAST, cube));
	else
		return (save_texture(flags, SPRITE_TEX, SPRITE, cube));
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

int		save_color(int *flags, int flag, t_cube *cube)
{
	char	**rgb;
	int		color;

	if (*flags & flag || ft_strarrlen(cube->info) != 2 ||
			((rgb = ft_split(cube->info[1], ',')) == NULL))
		return (-1);
	if (ft_strarrlen(rgb) != 3 || (create_color(rgb, &color)) < 0)
	{
		ft_free_strarr(rgb);
		return (-1);
	}
	if (flag & CEIL_COL)
		cube->map.ceil_color = color;
	else
		cube->map.floor_color = color;
	ft_free_strarr(rgb);
	*flags |= flag;
	return (0);
}

int		parse_color(int *flags, t_cube *cube)
{
	char	**info;

	info = cube->info;
	if (!ft_strcmp(*info, "C"))
	{
		if (save_color(flags, CEIL_COL, cube) < 0)
			return (-1);
	}
	else
	{
		if (save_color(flags, FLOOR_COL, cube) < 0)
			return (-1);
	}
	ft_free_strarr(info);
	return (0);
}

void	parse_identifier(int *flags, t_list *head, t_cube *cube)
{
	char	**info;

	info = cube->info;
	if (!ft_strcmp(*info, "R"))
	{
		if (parse_resolution(flags, cube) == -1)
			free_info_lst_quit(info, head, cube);
	}
	else if (!ft_strcmp(*info, "NO") || !ft_strcmp(*info, "SO") ||
			!ft_strcmp(*info, "WE") || !ft_strcmp(*info, "EA") ||
			!ft_strcmp(*info, "S"))
	{
		if (parse_texture(flags, cube) == -1)
			free_info_lst_quit(info, head, cube);
	}
	else if (!ft_strcmp(*info, "F") || !ft_strcmp(*info, "C"))
	{
		if (parse_color(flags, cube) == -1)
			free_info_lst_quit(info, head, cube);
	}
	else
		free_info_lst_quit(info, head, cube);
}

void	parse_line(char *line, int *flags, t_list *head, t_cube *cube)
{
	if ((cube->info = ft_split(line, ' ')) == NULL)
		free_lst_quit(head, cube);
	if (*(cube->info))
	{
		parse_identifier(flags, head, cube);
	}
	else
		free(cube->info);
}

void	set_rotation_angle(int position, t_cube *cube)
{
	if (position == 'N')
		cube->map.player.rotation_angle = PI / 2 * 3;
	else if (position == 'S')
		cube->map.player.rotation_angle = PI / 2;
	else if (position == 'W')
		cube->map.player.rotation_angle = PI;
	else if (position == 'E')
		cube->map.player.rotation_angle = 0;
}

int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int		check_row(char *str, t_cube *cube)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(VALID_MAP_CHARS, str[i]) == NULL)
			return (-1);
		if (str[i] == '2')
			cube->map.sprites++;
		if (ft_strchr(SPAWN_ORIENTATION, str[i]))
		{
			if (cube->map.player_found != 0)
				return (-1);
			cube->map.player_found++;
			cube->map.player.map_x = i;
			cube->map.player.map_y = cube->map.height;
			set_rotation_angle(str[i], cube);
			str[i] = '0';
		}
		i++;
	}
	cube->map.height++;
	cube->map.width = ft_max(i, cube->map.width);
	return (i < 3 ? -1 : 0);
}

int		check_map(t_list *trav, t_cube *cube)
{
	while (trav)
	{
		if (check_row(trav->content, cube) == -1)
			return (-1);
		trav = trav->next;
	}
	return (0);
}

void	set_sprite(int x, int y, int i, t_cube *cube)
{
	cube->sprites[i].map_x = x;
	cube->sprites[i].map_y = y;
	cube->sprites[i].texture_id = SPRITE;
	cube->row[x] = '0';
}

int		save_sprite_positions(t_list *trav, t_cube *cube)
{
	int		y;
	int		x;
	int		i;

	if ((cube->sprites = malloc(sizeof(t_sprite) * cube->map.sprites)) == NULL)
		return (-1);
	y = 0;
	i = 0;
	while (trav)
	{
		cube->row = trav->content;
		x = 0;
		while (cube->row[x])
		{
			if (cube->row[x] == '2')
			{
				set_sprite(x, y, i, cube);
				i++;
			}
			x++;
		}
		y++;
		trav = trav->next;
	}
	return (0);
}

int		save_row(char *row, int y, t_cube *cube)
{
	int	x;
	int	**grid;
	int	*grid_row;

	if ((grid_row = malloc(sizeof(int) * cube->map.width)) == NULL)
		return (-1);
	grid = cube->map.grid;
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
	while (x < cube->map.width)
	{
		grid[y][x] = 2;
		x++;
	}
	return (0);
}

void	free_int_matrix(int **matrix, size_t y)
{
	size_t	i;

	if (matrix)
	{
		i = 0;
		while (i < y)
		{
			free(matrix[i]);
			i++;
		}
	}
	free(matrix);
}

int		save_grid(t_list *trav, t_cube *cube)
{
	int	y;

	cube->map.grid = malloc(sizeof(int *) * cube->map.height);
	if (cube->map.grid == NULL)
		return (-1);
	y = 0;
	while (trav)
	{
		cube->row = trav->content;
		if (save_row(cube->row, y, cube) == -1)
		{
			free_int_matrix(cube->map.grid, y);
			return (-1);
		}
		y++;
		trav = trav->next;
	}
	return (0);
}

int		save_map(t_list *trav, t_cube *cube)
{
	if (cube->map.sprites != 0)
		if (save_sprite_positions(trav, cube) == -1)
			return (-1);
	if (save_grid(trav, cube) == -1)
		return (-1);
	return (0);
}

t_list	*skip_empty_lines(t_list *trav)
{
	while (trav && *(char *)trav->content == '\0')
		trav = trav->next;
	return (trav);
}

void	parse_map(t_list *trav, t_list *head, t_cube *cube)
{
	int	open;

	trav = skip_empty_lines(trav);
	if (check_map(trav, cube) == -1)
		free_lst_quit(head, cube);
	if (cube->map.player_found != 1 ||
			(cube->width >= 0 && cube->width < cube->map.width) ||
			(cube->height >= 0 && cube->height < cube->map.height))
		free_lst_quit(head, cube);
	if (save_map(trav, cube) == -1)
		free_lst_quit(head, cube);
	open = FALSE;
	boundary_fill(cube->map.player.map_x, cube->map.player.map_y, &open, cube);
	if (open == TRUE)
		free_lst_quit(head, cube);
	rev_boundary_fill(cube);
}

void	parse_list(t_list *head, t_cube *cube)
{
	t_list	*trav;
	int		flags;

	flags = 0;
	trav = head;
	while (trav)
	{
		if (flags < IDENTIFIERS)
		{
			parse_line(trav->content, &flags, head, cube);
			trav = trav->next;
		}
		else
		{
			parse_map(trav, head, cube);
			break ;
		}
	}
	if (flags != IDENTIFIERS)
		free_lst_quit(head, cube);
}

void	parse_cub(char *path, t_cube *cube)
{
	int		fd;
	int		error;
	char	*line;
	t_list	*head;

	head = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		quit_cube(cube, EXIT_FAILURE);
	line = NULL;
	while ((error = get_next_line(fd, &line)) > 0)
		lst_add_line(line, &head, cube);
	if (error != -1 && *line)
		lst_add_line(line, &head, cube);
	else
		free(line);
	ft_lstrev(&head);
	parse_list(head, cube);
	ft_lstclear(&head, free);
}
