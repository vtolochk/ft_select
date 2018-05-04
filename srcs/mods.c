/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 18:52:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 10:49:38 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_raw_mode(t_select *data)
{
	if (tgetent(NULL, getenv("TERM")) == -1)
		exit_error("The terminfo database could not be found\n");
	if (tcgetattr(0, &data->tty) == -1)
		exit_error("Can't get the parameters of the terminal\n");
	data->old_tty = data->tty;
	data->tty.c_lflag &= ~ECHO;
	data->tty.c_lflag &= ~ICANON;
	data->tty.c_cc[VMIN] = 1;
	if (tcsetattr(0, TCSAFLUSH, &data->tty) == -1)
		exit_error("Can't set parameters\n");
	tputs(tgetstr("ti", NULL), 1, &print_command);
	tputs(tgetstr("vi", NULL), 1, &print_command);
}

void	set_canonical_mode(t_select *data)
{
	tputs(tgetstr("ve", NULL), 1, &print_command);
	tputs(tgetstr("te", NULL), 1, &print_command);
	data->tty = data->old_tty;
	tcsetattr(0, TCSAFLUSH, &data->tty);
}
