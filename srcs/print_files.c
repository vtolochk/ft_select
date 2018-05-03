/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 10:41:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/04/27 10:41:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void init_helper(int *i, int *real_rows, t_files **lst, t_files *head)
{
	*i = 0;
	*lst = head;
	*real_rows = 1;
}
static void init_helper_2(int *available, int *biggest, t_select data, t_files *head)
{
	*available = get_rows(data, head);
	*biggest = get_biggest_len(head, data.list_len);
}

static int window_too_small(int available_rows, t_select data, int real, int biggest)
{
	if (available_rows == 0 || (available_rows == 1 && data.list_len > data.size.ws_row - 1) || (real * biggest > data.size.ws_col))
	{
		clr_screen(data);
		write(STDERR_FILENO, "Window size too small\n", 22);
		return (1);
	}
	return (0);
}

void print_files(t_select data, t_files *head, int x, int y)
{
	int i;
	int real_rows;
	int biggest_len;
	t_files *lst;
	int available_rows;

	init_helper(&i, &real_rows, &lst, head);
	init_helper_2(&available_rows, &biggest_len, data, head);
	while (i < data.list_len)
	{
		write(2, tgoto(tgetstr("cm", NULL), x, y), ft_strlen(tgoto(tgetstr("cm", NULL), x, y)));
		if (y >= data.size.ws_row - 1)
		{
			y = 0;
			real_rows++;
			x += biggest_len;
			continue ;
		}
		if (window_too_small(available_rows, data, real_rows, biggest_len))
			break ;
		print_file(lst);
		lst->row = y++;
		lst = lst->next;
		i++;
	}
}
