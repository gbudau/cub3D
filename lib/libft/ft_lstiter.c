/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 19:46:10 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/29 19:54:18 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	**plst;

	plst = &lst;
	if ((*plst) != NULL)
	{
		while ((*plst) != NULL)
		{
			f((*plst)->content);
			plst = &(*plst)->next;
		}
	}
}
