/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:40:47 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/03 21:25:08 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	const char *resetn;
	const char *ret;

	if (*need == '\0')
		return ((char *)hay);
	ret = hay;
	resetn = need;
	while (*hay && len)
	{
		need = resetn;
		while ((*hay == *need) && *hay != '\0' && *need != '\0' && len)
		{
			need++;
			hay++;
			len--;
		}
		if (*need == '\0')
			return ((char *)hay - (need - resetn));
		if (*hay == '\0' || len == '\0')
			return (NULL);
		hay = ++ret;
		len += (need - resetn);
		len--;
	}
	return (NULL);
}
