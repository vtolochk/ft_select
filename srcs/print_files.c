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
	write(1, "\n", 1);
	tputs(tgetstr("ue", NULL), 1, &print_command);
	tputs(tgetstr("se", NULL), 1, &print_command);
}

static void selected(char *string)
{
	tputs(tgetstr("so", NULL), 1, &print_command);
	write(1, string, ft_strlen(string));
	write(1, "\n", 1);
	tputs(tgetstr("se", NULL), 1, &print_command);
}

static void underline(char *string)
{
	tputs(tgetstr("us", NULL), 1, &print_command);
	write(1, string, ft_strlen(string));
	write(1, "\n", 1);
	tputs(tgetstr("ue", NULL), 1, &print_command);
}

void print_files(t_files *head, int list_len)
{
	t_files *lst;

	lst = head;
	while (list_len-- > 0)
	{
		if (lst->underline && lst->selected)
			underline_and_selected(lst->name);
		else if (lst->selected)
			selected(lst->name);
		else if (lst->underline)
			underline(lst->name);
		else
		{
			write(1, lst->name, ft_strlen(lst->name));
			write(1, "\n", 1);
		}
		lst = lst->next;
	}
}
