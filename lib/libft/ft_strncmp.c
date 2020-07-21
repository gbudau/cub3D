/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 20:32:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/20 20:36:18 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (!n || str1 == str2)
		return (0);
	while (*str1 && *str2 && (n-- - 1))
	{
		if (*str1 != *str2)
			return (((unsigned char)*str1) - ((unsigned char)*str2));
		str1++;
		str2++;
	}
	return (((unsigned char)*str1) - ((unsigned char)*str2));
}
