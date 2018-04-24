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

int print_command(int sign)
{
	write(STDERR_FILENO, &sign, 1);
	return (1);
}

int exit_error(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

void get_screen_size(t_select *data)
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &data->size);
}

int  main(int argc, char **argv)
{
	char key;
	t_select data;
	t_files *files;

	key = 0;
	if (!isatty(0))
		exit_error("Stdin is not terminal\n");
	set_raw_mode(&data);
	get_files(&files, argv, argc, &data.list_len);
	while (1)
	{
		get_screen_size(&data);
		print_files(files, data.list_len);
		read(0, &key, 8);
		if (key == ESC)
			break;
		if (key == 's')
		{
			char c = 27;
			write(1, &c, 1);
			write(1, "[1;C", 4);
		}
	}
	set_canonical_mode(&data);
	return (0);
}
