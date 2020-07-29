/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <gbudau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:53:27 by gbudau            #+#    #+#             */
/*   Updated: 2020/07/29 18:41:59 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	parse_identifier(int *flags, t_list *head, t_cub *cub)
{
	char	**info;

	info = cub->info;
	if (!ft_strcmp(*info, "R"))
	{
		if (parse_resolution(flags, cub) == -1)
			free_info_lst_quit(info, head, cub, ERR_IDENT);
	}
	else if (!ft_strcmp(*info, "NO") || !ft_strcmp(*info, "SO") ||
			!ft_strcmp(*info, "WE") || !ft_strcmp(*info, "EA") ||
			!ft_strcmp(*info, "S"))
	{
		if (parse_texture(flags, cub) == -1)
			free_info_lst_quit(info, head, cub, ERR_IDENT);
	}
	else if (!ft_strcmp(*info, "F") || !ft_strcmp(*info, "C"))
	{
		if (parse_color(flags, cub) == -1)
			free_info_lst_quit(info, head, cub, ERR_IDENT);
	}
	else
		free_info_lst_quit(info, head, cub, ERR_CUB);
}

static void	parse_line(char *line, int *flags, t_list *head, t_cub *cub)
{
	if ((cub->info = ft_split(line, ' ')) == NULL)
		free_lst_quit(head, cub, ERR_IDENT);
	if (*(cub->info))
	{
		parse_identifier(flags, head, cub);
	}
	else
		free(cub->info);
}

static void	parse_list(t_list *head, t_cub *cub)
{
	t_list	*trav;
	int		flags;

	flags = 0;
	trav = head;
	while (trav)
	{
		if (flags != IDENTIFIERS)
		{
			parse_line(trav->content, &flags, head, cub);
			trav = trav->next;
		}
		else
			break ;
	}
	if (flags != IDENTIFIERS)
		free_lst_quit(head, cub, ERR_CUB);
	parse_grid(trav, head, cub);
}

static void	lst_add_line(char *line, t_list **head, t_cub *cub)
{
	t_list	*node;

	node = NULL;
	if ((node = ft_lstnew(line)) == NULL)
		free_lst_quit(*head, cub, ERR_MEM);
	ft_lstadd_front(head, node);
}

void		parse_cub(char *path, t_cub *cub)
{
	int		fd;
	int		error;
	char	*line;
	t_list	*head;

	head = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		quit_cub(cub, EXIT_FAILURE, "Can't open .cub file");
	line = NULL;
	while ((error = get_next_line(fd, &line)) > 0)
		lst_add_line(line, &head, cub);
	if (error != -1 && *line)
		lst_add_line(line, &head, cub);
	else
		free(line);
	ft_lstrev(&head);
	if (close(fd))
		free_lst_quit(head, cub, "Can't close .cub file");
	parse_list(head, cub);
	ft_lstclear(&head, free);
}
