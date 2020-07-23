/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:57:28 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/22 16:39:22 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Assign substrings separated by any char in delim into split array
** Return the array of substrings or NULL in case of error
*/

static char		**ft_strtomatr(char **split, const char *s, const char *delim)
{
	char const	*word_start;
	int			i;
	size_t		state;

	i = -1;
	state = 0;
	while (*s != '\0')
	{
		if (ft_strchr(delim, *s))
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			word_start = s;
			i++;
		}
		if ((state && ft_strchr(delim, *(s + 1))) || (state && !*(s + 1)))
			if (!(split[i] = ft_strndup(word_start, s - word_start + 1)))
			{
				ft_free_strarr(split);
				return (NULL);
			}
		s++;
	}
	return (split);
}

/*
** Split the s string into substrings separated by
** any character found in delim
** Return the array of substrings or NULL in case of error
*/

char			**ft_split_str(const char *s, const char *delim)
{
	size_t		i;
	char		**split;

	if (s == NULL || delim == NULL)
		return (NULL);
	i = ft_str_count_s(s, delim);
	if (!(split = ft_calloc(i + 1, sizeof(char *))))
		return (NULL);
	return (ft_strtomatr(split, s, delim));
}
