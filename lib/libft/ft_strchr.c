/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:53:48 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/02 14:49:42 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char		*p;

	p = s;
	while (*p)
	{
		if (*p == (const char)c)
			return ((char *)p);
		p++;
	}
	if (*p == (const char)c)
		return ((char *)p);
	return (NULL);
}
