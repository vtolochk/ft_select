/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:40:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 11:19:23 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		move_right(t_files **files)
{
	int			find;
	t_files		*lst;

	lst = *files;
	find = lst->row;
	lst = lst->next;
	while (lst->row != find)
		lst = lst->next;
	lst->underline = 1;
}

static void		move_left(t_files **files)
{
	int			find;
	t_files		*lst;

	lst = *files;
	find = lst->row;
	lst = lst->prev;
	while (lst->row != find)
		lst = lst->prev;
	lst->underline = 1;
}

void			move_underline(t_files **files, t_select data, int direct)
{
	int			len;
	t_files		*lst;

	len = data.list_len;
	lst = *files;
	while (len > 0)
	{
		len--;
		if (lst->underline == 1)
		{
			lst->underline = 0;
			if (direct == ARROW_DOWN)
				lst->next->underline = 1;
			else if (direct == ARROW_UP)
				lst->prev->underline = 1;
			else if (direct == ARROW_RIGHT)
				move_right(&lst);
			else if (direct == ARROW_LEFT)
				move_left(&lst);
			break ;
		}
		lst = lst->next;
	}
}
