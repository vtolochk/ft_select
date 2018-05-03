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
	write(STDERR_FILENO, error, ft_strlen(error));
	exit(1);
}

void get_screen_size(struct winsize *size)
{
	ioctl(STDERR_FILENO, TIOCGWINSZ, size);
}

void move_right(t_files **files)
{
	int find;
	t_files *lst;

	lst = *files;
	find = lst->row;
	lst = lst->next;
	while (lst->row != find)
		lst = lst->next;
	lst->underline = 1;
}

void move_left(t_files **files)
{
	int find;
	t_files *lst;

	lst = *files;
	find = lst->row;
	lst = lst->prev;
	while (lst->row != find)
		lst = lst->prev;
	lst->underline = 1;
}

void move_underline(t_files **files, t_select data, int direction)
{
	int len;
	t_files *lst;

	len = data.list_len;
	lst = *files;
	while (len > 0)
	{
		len--;
		if (lst->underline == 1)
		{
			lst->underline = 0;
			if (direction == ARROW_DOWN)
				lst->next->underline = 1;
			else if (direction == ARROW_UP)
				lst->prev->underline = 1;
			else if (direction == ARROW_RIGHT)
				move_right(&lst);
			else if (direction == ARROW_LEFT)
				move_left(&lst);
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
	if (key == ESC || key == ESC_1)
		return (EXIT);
	else if (key == ARROW_UP)
		move_underline(files, *data, ARROW_UP);
	else if (key == ARROW_DOWN)
		move_underline(files, *data, ARROW_DOWN);
	else if (key == ARROW_LEFT)
		move_underline(files, *data, ARROW_LEFT);
	else if (key == ARROW_RIGHT)
		move_underline(files, *data, ARROW_RIGHT);
	else if (key == SPACE || key == SPACE_1)
		select_file(files, data->list_len);
	else if (key == BACKSPACE || key == BACKSPACE_1 || key == DELETE_KEY)
		remove_item(files, data);
	else if (key == ENTER)
		return (SEND);
	return (CONTINUE);
}

int number_of_seleceted_files(t_files *files, int len)
{
	t_files *lst;
	int selected_files;

	lst = files;
	selected_files = 0;
	while (len-- > 0)
	{
		if (lst->selected)
			selected_files++;
		lst = lst->next;
	}
	return (selected_files);
}

void print_selected_files(t_files *files, int len)
{
	t_files *lst;
	int selected_files;

	lst = files;
	selected_files = number_of_seleceted_files(files, len);
	while (len-- > 0)
	{
		if (lst->selected)
		{
			write(1, lst->name, ft_strlen(lst->name));
			if (selected_files > 1)
				write(1, " ", 1);
			selected_files--;
		}
		lst = lst->next;
	}
}

int display_files(t_select *data, t_files **files)
{
	int ret;

	get_screen_size(&data->size);
	print_files(*data, *files);
	ret = do_select(data, files);
	if (ret == EXIT)
		return (EXIT);
	else if (ret == SEND)
		return (SEND);
	clr_screen(*data);
	return (CONTINUE);
}

int  main(int argc, char **argv)
{
	int ret;
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
		ret = display_files(&data, &files);
		if (ret == EXIT || ret == SEND)
			break ;
	}
	set_canonical_mode(&data);
	if (ret == SEND)
		print_selected_files(files, data.list_len);
	free_list(&files, data.list_len);
	return (0);
}
