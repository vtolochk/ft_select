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

int do_select(t_select *data, t_files **files)
{
	int key;

	signals();
	read(2, &key, 4);
	if (key == ESC || key == ESC_1 || key == SIG_KILL || key == SIG_KILL_1)
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
	else if (key == PLUS)
		select_all(files, data->list_len);
	else if (key == MINUS)
		unselect_all(files, data->list_len);
	else if (key == ENTER || key == ENTER_1)
		return (SEND);
	return (CONTINUE);
}

int number_of_selected_files(t_files *files, int len)
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
	selected_files = number_of_selected_files(files, len);
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
	print_files(*data, *files, 0, 0);
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
	data_keeper(&data);
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
