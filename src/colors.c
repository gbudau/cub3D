/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:46:39 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/02 17:57:16 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Create 32 bit ARGB color from separate color values for A,R,G,B
*/

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Return the transparency(alpha) of the color
*/

int	get_t(int trgb)
{
	return (trgb >> 24 & 0xFF);
}

/*
** Return the Red value of the color
*/

int	get_r(int trgb)
{
	return (trgb >> 16 & 0xFF);
}

/*
** Return the Green value of the color
*/

int	get_g(int trgb)
{
	return (trgb >> 8 & 0xFF);
}

/*
** Return the Blue value of the color
*/

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
