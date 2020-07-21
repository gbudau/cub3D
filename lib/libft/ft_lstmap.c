/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:22:20 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/20 13:00:49 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*trav;
	t_list	*new_lst;
	t_list	*temp;

	trav = lst;
	new_lst = NULL;
	if (trav != NULL)
	{
		while (trav != NULL)
		{
			temp = ft_lstnew(f(trav->content));
			if (temp == NULL)
			{
				ft_lstclear(&new_lst, del);
				return (NULL);
			}
			ft_lstadd_front(&new_lst, temp);
			trav = trav->next;
		}
	}
	ft_lstrev(&new_lst);
	return (new_lst);
}
