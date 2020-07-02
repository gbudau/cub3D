/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:56:13 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/29 16:00:37 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *p2;

	if (new != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			p2 = ft_lstlast(*alst);
			p2->next = new;
		}
	}
}
