/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:39:35 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/03 22:10:41 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	if (dstsize == 0)
		return (ft_strlen(src));
	if (dst == NULL)
		return (0);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (j < dstsize - 1)
		{
			dst[j] = src[j];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (i);
}
