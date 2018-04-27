/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:24:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/04/27 18:24:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void sig_processing(int signal)
{
	if (signal == SIGWINCH)
	{
		ft_printf("you changed the window\n");
	}
}

void		signals(void)
{
	signal(SIGWINCH, sig_processing);
	signal(SIGABRT, sig_processing);
	signal(SIGINT, sig_processing);
	signal(SIGSTOP, sig_processing);
	signal(SIGCONT, sig_processing);
	signal(SIGTSTP, sig_processing);
	signal(SIGKILL, sig_processing);
	signal(SIGQUIT, sig_processing);
}
