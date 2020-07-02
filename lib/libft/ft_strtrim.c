/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:04:07 by gbudau            #+#    #+#             */
/*   Updated: 2019/12/01 17:15:40 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = s1;
	while (ft_strchr(set, *start) && *start)
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start;
	while (*(end + 1))
		end++;
	while (ft_strchr(set, *end) && end > s1)
		end--;
	return (ft_strndup(start, (end - start) + 1));
}
