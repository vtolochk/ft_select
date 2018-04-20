/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:51:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/04/20 15:04:44 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <term.h>
#include "ft_select.h"

int  main(void)
{
	char term_buf[2048];
	char *termtype = getenv ("TERM");
	int success;

	if (termtype == 0)
		printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");

	success = tgetent (term_buf, termtype);
	if (success < 0)
		printf("Could not access the termcap data base.\n");
	else if (success == 0)
		printf("Terminal type `%s' is not defined.\n", termtype);
	printf("name of term: %s\n", term_buf);
	return (0);
}
