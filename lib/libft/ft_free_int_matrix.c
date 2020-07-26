/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:14:29 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/25 19:14:37 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_int_matrix(int **matrix, size_t size)
{
	size_t	i;

	if (matrix)
	{
		i = 0;
		while (i < size)
		{
			free(matrix[i]);
			i++;
		}
	}
	free(matrix);
}
