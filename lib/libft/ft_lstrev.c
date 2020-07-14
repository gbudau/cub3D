/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 13:24:32 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/14 13:28:54 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrev(t_list *lst)
{
	t_list *prev;
	t_list *curr;
	t_list *temp;

	prev = NULL;
	curr = lst;
	while (curr != NULL)
	{
		temp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = temp->next;
	}
	return (prev);
}
