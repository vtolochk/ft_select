/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_one_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:56:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 11:02:55 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		underline_and_selected(char *string)
{
	tputs(tgetstr("so", NULL), 1, &print_command);
	tputs(tgetstr("us", NULL), 1, &print_command);
	write(STDERR_FILENO, string, ft_strlen(string));
	tputs(tgetstr("ue", NULL), 1, &print_command);
	tputs(tgetstr("se", NULL), 1, &print_command);
}

static void		selected(char *string)
{
	write(STDERR_FILENO, SELECTED, ft_strlen(SELECTED));
	tputs(tgetstr("so", NULL), 1, &print_command);
	write(STDERR_FILENO, string, ft_strlen(string));
	tputs(tgetstr("se", NULL), 1, &print_command);
	write(STDERR_FILENO, EOC, ft_strlen(EOC));
}

static void		underline(char *string)
{
	write(STDERR_FILENO, UNDERLINE, ft_strlen(UNDERLINE));
	tputs(tgetstr("us", NULL), 1, &print_command);
	write(STDERR_FILENO, string, ft_strlen(string));
	tputs(tgetstr("ue", NULL), 1, &print_command);
	write(STDERR_FILENO, EOC, ft_strlen(EOC));
}

void			print_file(t_files *lst)
{
	write(STDERR_FILENO, BLUE, ft_strlen(BLUE));
	if (lst->underline && lst->selected)
		underline_and_selected(lst->name);
	else if (lst->selected)
		selected(lst->name);
	else if (lst->underline)
		underline(lst->name);
	else
		write(STDERR_FILENO, lst->name, ft_strlen(lst->name));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, EOC, ft_strlen(EOC));
}
