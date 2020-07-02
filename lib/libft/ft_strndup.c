/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:39:19 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/30 19:59:46 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	if (len < n)
		return (ft_strdup(s1));
	if (!(ret = malloc(sizeof(char) * n + 1)))
		return (NULL);
	*(ret + n) = '\0';
	while (len-- && n--)
		*(ret + n) = *(s1 + n);
	return (ret);
}
