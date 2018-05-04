/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 10:41:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 11:27:23 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		init_help(int *i, int *real_rows, t_files **lst, t_files *head)
{
	*i = 0;
	*lst = head;
	*real_rows = 1;
}

static void		init_help2(int *avble, int *bgst, t_select data, t_files *head)
{
	*avble = get_rows(data, head);
	*bgst = get_biggest_len(head, data.list_len);
}

static void		next_line_help(int *y, int *x, int *real_rows, int biggest_len)
{
	*y = 0;
	(*real_rows)++;
	(*x) += biggest_len;
}

static int		wdw_small(int available_rows, t_select data, int real, int bgst)
{
	if (available_rows == 0 ||
	(available_rows == 1 && data.list_len > data.size.ws_row - 1) ||
	(real * bgst > data.size.ws_col))
	{
		clr_screen(data);
		write(STDERR_FILENO, WARNING, ft_strlen(WARNING));
		write(STDERR_FILENO, "Window size too small\n", 22);
		write(STDERR_FILENO, EOC, ft_strlen(EOC));
		return (1);
	}
	return (0);
}

void			print_files(t_select data, t_files *head, int x, int y)
{
	int			i;
	int			real_rows;
	int			biggest_len;
	int			available_rows;
	t_files		*lst;

	init_help(&i, &real_rows, &lst, head);
	init_help2(&available_rows, &biggest_len, data, head);
	while (i < data.list_len)
	{
		write(STDERR_FILENO, tgoto(tgetstr("cm", NULL), x, y), \
		ft_strlen(tgoto(tgetstr("cm", NULL), x, y)));
		if (y >= data.size.ws_row - 1)
		{
			next_line_help(&y, &x, &real_rows, biggest_len);
			continue ;
		}
		if (wdw_small(available_rows, data, real_rows, biggest_len))
			break ;
		print_file(lst);
		lst->row = y++;
		lst = lst->next;
		i++;
	}
}
