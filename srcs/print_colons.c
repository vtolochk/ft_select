/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:05:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/04/27 17:05:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

size_t get_colums(t_select data, t_files *head)
{
	size_t colums;
	size_t word_len;

	colums = 0;
	word_len = get_biggest_len(head, data.list_len);
	word_len++;
	while (word_len < data.size.ws_col)
	{
		colums++;
		word_len += word_len;
	}
	return (colums);
}

int print_colons(t_select data, t_files *head)
{
	//ft_printf("biggest_len: %d, size.ws_col: %d\n", get_biggest_len(head, data.list_len), data.size.ws_col);
	if (data.list_len > data.size.ws_row - 1 || get_biggest_len(head, data.list_len) > data.size.ws_col)
	{
		write(0, "Not enough space", 16);
		return (1);
	}
//	if (data.list_len < data.size.ws_row - 1)
//		return (0);
	//ft_printf("you will have %d colums\n", get_colums(data, head));
	return (0);
}