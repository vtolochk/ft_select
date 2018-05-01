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

static void underline_and_selected(char *string)
{
	tputs(tgetstr("so", NULL), 1, &print_command);
	tputs(tgetstr("us", NULL), 1, &print_command);
	write(1, string, ft_strlen(string));
	tputs(tgetstr("ue", NULL), 1, &print_command);
	tputs(tgetstr("se", NULL), 1, &print_command);
}

static void selected(char *string)
{
	tputs(tgetstr("so", NULL), 1, &print_command);
	write(1, string, ft_strlen(string));
	tputs(tgetstr("se", NULL), 1, &print_command);
}

static void underline(char *string)
{
	tputs(tgetstr("us", NULL), 1, &print_command);
	write(1, string, ft_strlen(string));
	tputs(tgetstr("ue", NULL), 1, &print_command);
}

void print_file(t_files *lst)
{
	if (lst->underline && lst->selected)
		underline_and_selected(lst->name);
	else if (lst->selected)
		selected(lst->name);
	else if (lst->underline)
		underline(lst->name);
	else
		write(1, lst->name, ft_strlen(lst->name));
}

size_t get_biggest_len(t_files *head, int lst_len)
{
	int i;
	size_t temp;
	size_t biggest_len;
	t_files *lst;

	i = 0;
	biggest_len = 0;
	lst = head;
	while (i < lst_len)
	{
		temp = ft_strlen(lst->name);
		if (temp > biggest_len)
			biggest_len = temp;
		i++;
		lst = lst->next;
	}
	return (++biggest_len);
}

size_t get_cols(t_select data, t_files *head)
{
	size_t colums;
	size_t word_len;

	colums = 0;
	word_len = get_biggest_len(head, data.list_len);
	while (word_len <= data.size.ws_col - 1)
	{
		colums++;
		word_len += word_len;
	}
	return (colums);
}

void print_files(t_select data, t_files *head)
{
	int biggest_len = get_biggest_len(head, data.list_len);
	size_t real_cols = 1;
	size_t avaliable_cols = get_cols(data, head);
	t_files *lst = head;
	int y = 0;
	int x = 0;
	int i = 0;

	while (i < data.list_len)
	{
		write(2, tgoto(tgetstr("cm", NULL), x, y), ft_strlen(tgoto(tgetstr("cm", NULL), x, y)));
		if (y >= data.size.ws_row - 1)
		{
			y = 0;
			real_cols++;
			x += biggest_len;
			continue ;
		}
		if (avaliable_cols == 0 || (avaliable_cols == 1 && data.list_len > data.size.ws_row - 1) || (real_cols * biggest_len > data.size.ws_col))
		{
			clr_screen(data);
			write(1, "Window size too small\n", 22);
			break ;
		}
		print_file(lst);
		write(1, "\n", 1);
		lst = lst->next;
		y++;
		i++;
	}
}
