/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:21:48 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/28 18:37:04 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	str_to_color(char *str)
{
	int		color;
	int		len;

	len = strlen_isdigit(str);
	if (len < 1 || len > 3 ||
			(len != 1 && *str == '0'))
		return (-1);
	color = ft_atoi(str);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	create_color(char **rgb, int *color)
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

static int	save_color(int *flags, int flag, t_cub *cub)
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

int			parse_color(int *flags, t_cub *cub)
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
