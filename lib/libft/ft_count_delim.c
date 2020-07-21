/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_delim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:00:13 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/20 14:00:26 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_delim(char const *s, char c)
{
	size_t i;
	size_t state;

	i = 0;
	state = OUT;
	while (*s != '\0')
	{
		if (*s == c)
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			i++;
		}
		s++;
	}
	return (i);
}
