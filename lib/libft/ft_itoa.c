/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:37:09 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/23 22:03:35 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_nblen(long int nb)
{
	if (nb == 0)
		return (0);
	return (1 + ft_nblen(nb / 10));
}

static char		*ft_nbtostrarr(char *ret, long int nb, long int len, int i)
{
	while (len > 0)
	{
		if (len >= i)
		{
			len--;
			ret[len] = (nb % 10) + '0';
			nb /= 10;
		}
	}
	return (ret);
}

char			*ft_itoa(int n)
{
	long int	nb;
	char		*ret;
	long int	len;
	long int	s;
	int			i;

	if (n == 0)
		return (ft_strdup("0"));
	nb = (long int)n;
	len = ft_nblen(n);
	s = (n < 0) ? 1 : 0;
	if (!(ret = ft_calloc(sizeof(char), len + 1 + s)))
		return (NULL);
	i = 0;
	if (n < 0)
	{
		ret[i] = '-';
		i++;
		nb *= -1;
	}
	ft_nbtostrarr(&ret[i], nb, len, i);
	return (ret);
}
