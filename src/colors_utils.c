/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:55:19 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/02 18:18:35 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Adds shading, accepts a double (distance) and a int (color) as arguments,
** 0 will add no shading to the color whilst 1 will make the color
** completely dark, 0.5 will dim it halfway, and .25 a quarter way.
*/

int	add_shade(double distance, int trgb)
{
	int t;
	int r;
	int g;
	int b;

	t = get_t(trgb);
	r = get_r(trgb) * (1 - distance);
	g = get_g(trgb) * (1 - distance);
	b = get_b(trgb) * (1 - distance);
	return (create_trgb(t, r, g, b));
}

/*
** Adds tint, tint accepts a double (distance) and a int (color) as arguments,
** 0 will add no tint to the color whilst 1 will make the color
** completely white, 0.5 will light it halfway, and .25 a quarter way.
*/

int	add_tint(double distance, int trgb)
{
	int t;
	int r;
	int g;
	int b;

	t = get_t(trgb);
	r = get_r(trgb);
	r = r + (255 - r) * distance;
	g = get_g(trgb);
	g = g + (255 - g) * distance;
	b = get_b(trgb);
	b = b + (255 - b) * distance;
	return (create_trgb(t, r, g, b));
}

/*
** get_opposite is a function that accepts a int (color)
** as argument and that will invert the color accordingly.
*/

int	get_oposite(int trgb)
{
	int t;
	int r;
	int g;
	int b;

	t = 255 - get_t(trgb);
	r = 255 - get_r(trgb);
	g = 255 - get_g(trgb);
	b = 255 - get_b(trgb);
	return (create_trgb(t, r, g, b));
}
