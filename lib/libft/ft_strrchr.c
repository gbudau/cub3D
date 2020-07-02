/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:42:30 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/12 18:17:58 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	size_t		len;
	const char	*str;

	ch = c;
	str = s;
	len = ft_strlen(str);
	while (len)
	{
		if (*(str + len) == ch)
			return ((char *)(str + len));
		len--;
	}
	if (*str == ch)
		return ((char *)str);
	return (NULL);
}
