/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:32:43 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/02 09:55:52 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	char const	*s;

	if (dst == src)
		return (dst);
	d = dst;
	s = src;
	if (s < d)
	{
		while (len--)
			d[len] = s[len];
		return (dst);
	}
	else
		ft_memcpy(d, s, len);
	return (dst);
}
