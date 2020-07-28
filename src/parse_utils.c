/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:37:44 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/28 18:08:51 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_lst_quit(t_list *head, t_cub *cub)
{
	ft_lstclear(&head, free);
	quit_cub(cub, EXIT_FAILURE);
}

void	free_info_lst_quit(char **info, t_list *head, t_cub *cub)
{
	ft_free_strarr(info);
	free_lst_quit(head, cub);
}

int		strlen_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (i);
}
