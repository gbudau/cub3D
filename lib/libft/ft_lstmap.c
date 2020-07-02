/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:22:20 by gbudau            #+#    #+#             */
/*   Updated: 2019/11/30 18:31:13 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**temp;
	t_list	*ret;
	int		i;
	int		j;

	temp = &lst;
	i = ft_lstsize(lst);
	if ((*temp) != NULL)
	{
		ret = NULL;
		while ((*temp) != NULL)
		{
			ft_lstadd_back(&ret, ft_lstnew(f((*temp)->content)));
			temp = &(*temp)->next;
		}
		j = ft_lstsize(ret);
		if (j == i)
			return (ret);
		else
			ft_lstclear(&ret, del);
	}
	return (lst);
}
