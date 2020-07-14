/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 02:04:46 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/14 11:30:19 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned	nbr;
	int			sign;

	while (ft_isspace(*str))
		str++;
	nbr = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '+') ? 1 : -1;
	while (ft_isdigit(*str))
		nbr = *str++ - '0' + nbr * 10;
	return ((int)nbr * sign);
}
