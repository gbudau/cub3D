/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:25:10 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/14 13:19:13 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *trav;

	trav = lst;
	if (trav == NULL)
		return (trav);
	while (trav->next != NULL)
		trav = trav->next;
	return (trav);
}
