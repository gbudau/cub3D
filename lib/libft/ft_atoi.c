/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 02:04:46 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/16 22:08:09 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long int	nbr;
	const char				*s;
	int						pon;
	int						i;

	s = str;
	while (ft_isspace(*s))
		s++;
	nbr = 0;
	pon = 1;
	if (*s == '-' || *s == '+')
		pon = (*s++ == '+') ? 1 : -1;
	i = 0;
	while (ft_isdigit(*s) && ++i)
		nbr = *s++ - '0' + nbr * 10;
	if ((i > 19 && pon == -1) || (nbr > 9223372036854775808uLL && pon == -1))
		return (0);
	else if ((i > 19 && pon == 1) || (nbr > 9223372036854775807uLL && pon == 1))
		return (-1);
	return ((int)nbr * pon);
}
