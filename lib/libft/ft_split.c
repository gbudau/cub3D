/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:19:21 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/22 18:14:04 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wn(char const *s, char c)
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

static char		**ft_strtomatr(char **split, char const *s, char c)
{
	char const	*ws;
	int			j;
	size_t		state;

	j = -1;
	state = 0;
	while (*s != '\0')
	{
		if (*s == c)
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			ws = s;
			j++;
		}
		if ((state == IN && *(s + 1) == c) || (state == IN && *(s + 1) == '\0'))
			split[j] = ft_strndup(ws, s - ws + 1);
		s++;
	}
	return (split);
}

char			**ft_split(char const *s, char c)
{
	size_t		i;
	char		**split;

	if (s == NULL)
		return (NULL);
	i = ft_wn(s, c);
	if (!(split = ft_calloc(i + 1, sizeof(char *))))
		return (NULL);
	return (ft_strtomatr(split, s, c));
}
