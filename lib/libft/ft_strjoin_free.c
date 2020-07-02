/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:01:20 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/01 20:01:41 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Join s1 and s2 and return the new string
** flag(1) - Free s1
** flag(2) - Free s2
** flag(12) - Free both
*/

char	*ft_strjoin_free(char *s1, char *s2, size_t flag)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (flag == 1)
		free(s1);
	else if (flag == 2)
		free(s2);
	else if (flag == 12)
	{
		free(s1);
		free(s2);
	}
	return (ret);
}
