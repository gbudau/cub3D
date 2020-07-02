/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:35:40 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/02 12:27:03 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	unsigned const char *s;

	d = dst;
	s = src;
	while (n--)
	{
		*d = *s;
		if (*s == (unsigned char)c)
			return ((void *)++d);
		d++;
		s++;
	}
	return (NULL);
}
