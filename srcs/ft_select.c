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

void move_underline(t_files **files, int len, char direction)
{
	t_files *lst;

	lst = *files;
	while (len > 0)
	{
		len--;
		if (lst->underline == 1)
		{
			lst->underline = 0;
			if (direction == DOWN)
				lst->next->underline = 1;
			else
				lst->prev->underline = 1;
			break ;
		}
		lst = lst->next;
	}
}

void clr_screen()
{
	tputs(tgetstr("cl", NULL), 1, &print_command);
}

void select_file(t_files **files, int len)
{
	t_files *lst;

	lst = *files;
	while (len > 0)
	{
		len--;
		if (lst->underline && lst->selected)
		{
			lst->selected = 0;
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

int  main(int argc, char **argv)
{
	ssize_t ret;
	char key[6];
	t_select data;
	t_files *files;

	if (!isatty(0))
		exit_error("Stdin is not terminal\n");
	set_raw_mode(&data);
	get_files(&files, argv, argc, &data.list_len);
	while (1)
	{
		get_screen_size(&data);
		print_files(files, data.list_len);
		ret = read(0, &key, 6);
		if (*key == ESC && ret == 1)
			break ;
		else if (*key == ESC && *(key + 1) == BRACKET)
		{
			if (*(key + 2) == 'A')
				move_underline(&files, data.list_len, UP);
			if (*(key + 2) == 'B')
				move_underline(&files, data.list_len, DOWN);
		}
		if (key[0] == 32)
		{
			select_file(&files, data.list_len);
		}
		clr_screen();
	}
	set_canonical_mode(&data);
	return (0);
}
