/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:12:35 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/20 17:09:45 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
