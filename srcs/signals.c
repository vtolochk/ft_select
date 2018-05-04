/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:24:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 11:04:41 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		sig_processing(int sig_number)
{
	char		buf[4];
	t_select	*data;

	data = data_keeper(NULL);
	if (sig_number == SIGWINCH)
	{
		buf[0] = 0;
		ioctl(STDERR_FILENO, TIOCSTI, buf);
	}
	else if (sig_number == SIGINT || sig_number == SIGABRT ||
	sig_number == SIGSTOP || sig_number == SIGKILL || sig_number == SIGQUIT)
	{
		buf[0] = -1;
		ioctl(STDERR_FILENO, TIOCSTI, buf);
	}
	else if (sig_number == SIGTSTP)
		stop_handler(data);
	else if (sig_number == SIGCONT)
		continue_handler(data);
}

void			continue_handler(t_select *data)
{
	char buf[4];

	clr_screen(*data);
	tcsetattr(0, TCSAFLUSH, &data->tty);
	tputs(tgetstr("ti", NULL), 1, &print_command);
	tputs(tgetstr("vi", NULL), 1, &print_command);
	buf[0] = 0;
	ioctl(STDERR_FILENO, TIOCSTI, buf);
}

void			stop_handler(t_select *data)
{
	tputs(tgetstr("ve", NULL), 1, &print_command);
	tputs(tgetstr("te", NULL), 1, &print_command);
	tcsetattr(0, TCSAFLUSH, &data->old_tty);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\032");
}

void			signals(void)
{
	signal(SIGINT, sig_processing);
	signal(SIGSTOP, sig_processing);
	signal(SIGCONT, sig_processing);
	signal(SIGABRT, sig_processing);
	signal(SIGQUIT, sig_processing);
	signal(SIGTSTP, sig_processing);
	signal(SIGKILL, sig_processing);
	signal(SIGWINCH, sig_processing);
}
