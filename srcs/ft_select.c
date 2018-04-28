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

void get_screen_size(struct winsize *size)
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, size);
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

void clr_screen(t_select data)
{
	int i;

	i = 0;
	while (i < data.size.ws_row)
	{
		write(2, tgoto(tgetstr("cm", NULL), 0, i), ft_strlen(tgoto(tgetstr("cm", NULL), 0, i)));
		write(2, tgetstr("ce", NULL), ft_strlen(tgetstr("ce", NULL)));
		i++;
	}
	write(2, tgoto(tgetstr("cm", NULL), 0, 0), ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
}

void select_file(t_files **files, int len)
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

int do_select(t_select *data, t_files **files)
{
	int key;

	signals();
	read(2, &key, 4);
	if (key == ESC)
		return (EXIT);
	else if (key == ARROW_UP)
		move_underline(files, data->list_len, UP);
	else if (key == ARROW_DOWN)
		move_underline(files, data->list_len, DOWN);
	else if (key == SPACE)
		select_file(files, data->list_len);
	else if (key == BACKSPACE || key == DELETE_KEY)
		remove_item(files, data);
	return (CONTINUE);
}

int display_files(t_select *data, t_files **files)
{
	get_screen_size(&data->size);
	print_files(*data, *files);
	if (do_select(data, files) == EXIT)
		return (EXIT);
	clr_screen(*data);
	return (CONTINUE);
}

int  main(int argc, char **argv)
{
	t_select data;
	t_files *files;

	if (argc == 1)
		exit_error("Usage: ft_select [some files]\n");
	if (!isatty(0))
		exit_error("Stdin is not terminal\n");
	set_raw_mode(&data);
	get_files(&files, argv, argc, &data.list_len);
	while (1)
	{
		if (display_files(&data, &files) == EXIT)
			break ;
	}
	set_canonical_mode(&data);
	//putstr selected files with spaces
	free_list(&files, data.list_len);
	return (0);
}
