/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:19:21 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/20 18:46:49 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**free_strarray(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char		**ft_strtomatr(char **split, char const *s, char c)
{
	char const	*word_start;
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
			word_start = s;
			j++;
		}
		if ((state == IN && *(s + 1) == c) || (state == IN && *(s + 1) == '\0'))
			if ((split[j] = ft_strndup(word_start, s - word_start + 1)) == NULL)
				return (free_strarray(split));
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
	i = ft_count_delim(s, c);
	if (!(split = ft_calloc(i + 1, sizeof(char *))))
		return (NULL);
	return (ft_strtomatr(split, s, c));
}
