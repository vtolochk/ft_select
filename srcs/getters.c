/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 19:37:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/03 19:37:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void get_screen_size(struct winsize *size)
{
	ioctl(STDERR_FILENO, TIOCGWINSZ, size);
}

int get_biggest_len(t_files *head, int lst_len)
{
	int i;
	int temp;
	int biggest_len;
	t_files *lst;

	i = 0;
	biggest_len = 0;
	lst = head;
	while (i < lst_len)
	{
		temp = ft_strlen(lst->name);
		if (temp > biggest_len)
			biggest_len = temp;
		i++;
		lst = lst->next;
	}
	return (++biggest_len);
}

int get_rows(t_select data, t_files *head)
{
	int rows;
	int word_len;

	rows = 0;
	word_len = get_biggest_len(head, data.list_len);
	while (word_len <= data.size.ws_col - 1)
	{
		rows++;
		word_len += word_len;
	}
	return (rows);
}
