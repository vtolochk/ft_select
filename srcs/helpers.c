/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:42:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 10:46:10 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			print_command(int sign)
{
	write(STDERR_FILENO, &sign, 1);
	return (1);
}

int			exit_error(char *error)
{
	write(STDERR_FILENO, WARNING, ft_strlen(WARNING));
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, EOC, ft_strlen(EOC));
	exit(1);
}

t_select	*data_keeper(t_select *dt)
{
	static t_select *data;

	if (dt)
		data = dt;
	return (data);
}

void		clr_screen(t_select data)
{
	int i;

	i = 0;
	while (i < data.size.ws_row)
	{
		write(2, tgoto(tgetstr("cm", NULL), 0, i), \
		ft_strlen(tgoto(tgetstr("cm", NULL), 0, i)));
		write(2, tgetstr("ce", NULL), ft_strlen(tgetstr("ce", NULL)));
		i++;
	}
	write(2, tgoto(tgetstr("cm", NULL), 0, 0), \
	ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
}

void		select_file(t_files **files, int len)
{
	t_files *lst;

	lst = *files;
	while (len-- > 0)
	{
		if (lst->underline && lst->selected)
		{
			lst->selected = 0;
			lst->underline = 0;
			lst->next->underline = 1;
			break ;
		}
		if (lst->underline)
		{
			lst->selected = 1;
			lst->underline = 0;
			lst->next->underline = 1;
			break ;
		}
		lst = lst->next;
	}
}
