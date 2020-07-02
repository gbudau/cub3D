/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:54:22 by gbudau            #+#    #+#             */
/*   Updated: 2020/06/22 17:54:23 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (*str1 != '\0')
	{
		if (ft_strchr(str2, *str1) != NULL)
			return (i);
		str1++;
		i++;
	}
	return (i);
}
