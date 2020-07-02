/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:01:46 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/18 18:39:55 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	ft_strlcpy(ret + ft_strlen(s1), s2, len + 1);
	return (ret);
}
