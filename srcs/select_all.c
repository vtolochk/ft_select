/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:11:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 11:03:25 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	select_all(t_files **files, int list_len)
{
	t_files *lst;

	lst = *files;
	while (list_len--)
	{
		lst->selected = 1;
		lst = lst->next;
	}
}

void	unselect_all(t_files **files, int list_len)
{
	t_files *lst;

	lst = *files;
	while (list_len--)
	{
		lst->selected = 0;
		lst = lst->next;
	}
}
